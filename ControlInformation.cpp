/*****************************************************************************
 * FILE NAME    : ControlInformation.cpp
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "ControlInformation.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : ControlInformation
 *****************************************************************************/
ControlInformation::ControlInformation
() : SignalsInformation()
{
}

/*****************************************************************************!
 * Function : ~ControlInformation
 *****************************************************************************/
ControlInformation::~ControlInformation
()
{
}

/*****************************************************************************!
 * Function : AddControl
 *****************************************************************************/
void
ControlInformation::AddControl
(NCUControlSignal* InControl)
{
  if ( NULL == InControl ) {
    return;
  }
  controls << InControl;
}

/*****************************************************************************!
 * Function : FindControlByID
 *****************************************************************************/
NCUControlSignal*
ControlInformation::FindControlByID
(int InTrack, int InID)
{
  for ( auto i : controls ) {
    if ( i->GetTrack() == InTrack && i->GetID() == InID ) {
      return i;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : SQLRead
 *****************************************************************************/
void
ControlInformation::SQLRead
(sqlite3* InDatabase)
{
  NCUControlSignal*                     control;
  bool                                  finished;
  int                                   n;
  sqlite3_stmt*                         statement;
  QString                               sqlStatement;
  QString                               s;
  
  sqlStatement = QString("SELECT "
                         "Track,"               // 0
                         "Eq,"                  // 1
                         "SID,"                 // 2
                         "CTRLName,"            // 3
                         "Unit,"                // 4
                         "SIndx,"               // 5
                         "SChan,"               // 6
                         "ValType,"             // 7
                         "Defaults,"            // 8
                         "Range,"               // 9
                         "DisplayAttr,"         // 10
                         "CtrlAttr,"            // 11
                         "Threshold,"           // 12
                         "CableExpRPN,"         // 13
                         "CableExpFull,"        // 14
                         "Auth,"                // 15
                         "DisplayID,"           // 16
                         "DispFmt,"             // 17
                         "ChID,"                // 18
                         "CStep,"               // 19
                         "CParam,"              // 20
                         "CexpRPN,"             // 21
                         "CexpFullDispExp,"     // 22
                         "States,"              // 23
                         "CAction "             // 24                         
                         "FROM Control ORDER by CAST(Eq AS INTEGER), CAST(SID AS INTEGER), Track;");

  n = sqlite3_prepare_v2(InDatabase, sqlStatement.toStdString().c_str(), sqlStatement.length(), &statement, NULL);
  if ( n != SQLITE_OK ) {

    QMessageBox box = QMessageBox(QMessageBox::Critical,
                                  "sqlite3_prepare_v2 Fail",
                                  QString("sqlite3_prepare_v2() FAIL\n"
                                          "%1 : %2\n"
                                          "%3\n"
                                          "%4")
                                  .arg(__FILE__).arg(__LINE__)
                                  .arg(sqlStatement)
                                  .arg(sqlite3_errstr(n)));
    box.exec();
    exit(EXIT_FAILURE);
  }

  //!
  finished = false;
  while ( ! finished ) {
    n = sqlite3_step(statement);
    switch (n) {
      case SQLITE_BUSY : {
        break;
      }
      
      case SQLITE_DONE : {
        finished = true;
        break;
      }
      
      case SQLITE_ROW : {
        control = new NCUControlSignal();
        control->SetTrack(sqlite3_column_int(statement, 0));

        s = QString((char*)sqlite3_column_text(statement, 1));
        control->SetID(s.toInt());
        
        s = QString((char*)sqlite3_column_text(statement, 2));
        control->SetType(s.toInt());

        //!
        control->SetValue("CTRLName",           QString((char*)sqlite3_column_text(statement, 3)));
        control->SetValue("Unit",               QString((char*)sqlite3_column_text(statement, 4)));
        control->SetValue("SIndx",              QString((char*)sqlite3_column_text(statement, 5)));
        control->SetValue("SChan",              QString((char*)sqlite3_column_text(statement, 6)));
        control->SetValue("ValType",            QString((char*)sqlite3_column_text(statement, 7)));
        control->SetValue("Defaults",           QString((char*)sqlite3_column_text(statement, 8)));
        control->SetValue("Range",              QString((char*)sqlite3_column_text(statement, 9)));
        control->SetValue("DisplayAttr",        QString((char*)sqlite3_column_text(statement, 10)));
        control->SetValue("CtrlAttr",           QString((char*)sqlite3_column_text(statement, 11)));
        control->SetValue("Threshold",          QString((char*)sqlite3_column_text(statement, 12)));
        control->SetValue("CableExpRPN",        QString((char*)sqlite3_column_text(statement, 13)));
        control->SetValue("CableExpFull",       QString((char*)sqlite3_column_text(statement, 14)));
        control->SetValue("Auth",               QString((char*)sqlite3_column_text(statement, 15)));
        control->SetValue("DisplayID",          QString((char*)sqlite3_column_text(statement, 16)));
        control->SetValue("DispFmt",            QString((char*)sqlite3_column_text(statement, 17)));
        control->SetValue("ChID",               QString((char*)sqlite3_column_text(statement, 18)));
        control->SetValue("CStep",              QString((char*)sqlite3_column_text(statement, 19)));
        control->SetValue("CParam",             QString((char*)sqlite3_column_text(statement, 20)));
        control->SetValue("CexpRPN",            QString((char*)sqlite3_column_text(statement, 21)));
        control->SetValue("CexpFullDispExp",    QString((char*)sqlite3_column_text(statement, 22)));
        control->SetValue("States",             QString((char*)sqlite3_column_text(statement, 23)));
        control->SetValue("CAction",            QString((char*)sqlite3_column_text(statement, 24)));
        controls << control;
        break;
      }
      
      case SQLITE_ERROR : {
        break;
      }
      
      case SQLITE_MISUSE : {
        break;
      }
    }

  };

  sqlite3_finalize(statement);
  CreatePairs();
}

/*****************************************************************************!
 * Function : GetCountByTrack
 *****************************************************************************/
int
ControlInformation::GetCountByTrack
(int InTrack)
{
  int                                   n;

  n = 0;

  for ( auto i : controls ) {
    if ( i->GetTrack() == InTrack ) {
      n++;
    }
  }
  return n;
}

/*****************************************************************************!
 * Function : CreatePairs
 *****************************************************************************/
void
ControlInformation::CreatePairs(void)
{
  ControlSignalPair*                    controlPair;
  NCUControlSignal*                     e;
  int                                   i;
  int                                   n;

  n = controls.size();
  for (i = 0; i < n; i++) {
    e = controls[i];
    if ( e->Track != 2 ) {
      continue;
    }

    controlPair = new ControlSignalPair(e->ID, e->Type, e, NULL);
    controlPairs << controlPair;
  }

  for ( i = 0; i < n; i++ ){
    e = controls[i];
    if ( e->Track != 3 ) {
      continue;
    }
    controlPair = FindPairByID(e->ID, e->Type);
    if ( NULL == controlPair ) {
      controlPair = new ControlSignalPair(e->ID, e->Type, NULL, e);
      controlPairs << controlPair;
      continue;
    }
    controlPair->AddTrack3Signal(e);
  }
}

/*****************************************************************************!
 * Function : FindPairByID
 *****************************************************************************/
ControlSignalPair*
ControlInformation::FindPairByID
(int InID, int InSID)
{
  int                                   i, n;
  ControlSignalPair*                    pair;

  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    pair = controlPairs[i];
    if ( pair->GetID() == InID && pair->GetSID() == InSID ) {
      return pair;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetTrack2Count
 *****************************************************************************/
int
ControlInformation::GetTrack2Count(void)
{
  return GetTrackCount(2);
}

/*****************************************************************************!
 * Function : GetTrack3Count
 *****************************************************************************/
int
ControlInformation::GetTrack3Count(void)
{
  return GetTrackCount(3);
}

/*****************************************************************************!
 * Function : GetTrackCount
 *****************************************************************************/
int
ControlInformation::GetTrackCount
(int InTrack)
{
  int                                   count;
  int                                   i;
  int                                   n;
  NCUControlSignal*                     e;

  count = 0;
  n = controls.size();
  for (i = 0; i < n; i++) {
    e = controls[i];

    if ( e->Track == InTrack ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetTrack2MissingCount
 *****************************************************************************/
int
ControlInformation::GetTrack2MissingCount(void)
{
  ControlSignalPair*                    ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    ep = controlPairs[i];
    if ( ep->GetTrack2() == NULL ) {
      count++;
    }
  }
  return count;  
}

/*****************************************************************************!
 * Function : GetTrack3MissingCount
 *****************************************************************************/
int
ControlInformation::GetTrack3MissingCount(void)
{
  ControlSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    ep = controlPairs[i];
    if ( ep->GetTrack3() == NULL ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetTrackDifferCount
 *****************************************************************************/
int
ControlInformation::GetTrackDifferCount(void)
{
  ControlSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    ep = controlPairs[i];
    if ( ep->Differ() ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetPairByIndex
 *****************************************************************************/
ControlSignalPair*
ControlInformation::GetPairByIndex
(int InIndex)
{
  if ( InIndex >= controlPairs.size() ) {
    return NULL;
  }
  return controlPairs[InIndex];
}

/*****************************************************************************!
 * Function : GetPairCount
 *****************************************************************************/
int
ControlInformation::GetPairCount
()
{
  return controlPairs.size();
}
