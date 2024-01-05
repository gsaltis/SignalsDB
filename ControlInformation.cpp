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
#include "main.h"

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
  int                                   i;
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
                         "ControlName,"         // 3
                         "ResourceID,"          // 4
                         "Unit,"                // 5
                         "SamplerIndx,"         // 6
                         "SamplerChannel,"      // 7
                         "ValueType,"           // 8
                         "Defaults,"            // 9
                         "Range,"               // 10
                         "DisplayAttr,"         // 11
                         "ControlAttr,"         // 12
                         "Threshold,"           // 13
                         "CableExprRPN,"        // 14
                         "CableExprFull,"       // 15
                         "AuthLevel,"           // 16
                         "DisplayID,"           // 17
                         "DisplayFormat,"       // 18
                         "ChannelID,"           // 19
                         "ControlStep,"         // 20
                         "ControlParam,"        // 21
                         "ControlExprRPN,"      // 22
                         "ControlExprFull,"     // 23
                         "States,"              // 24
                         "OnControlAction,"     // 25
                         "DispExprRPN,"         // 26
                         "DispExprFull "        // 27
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
        i = 3;
        control->SetValue("ControlName",        QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ResourceID",         QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("Unit",               QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("SamplerIndx",        QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("SamplerChannel",     QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ValueType",          QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("Defaults",           QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("Range",              QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("DisplayAttr",        QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ControlAttr",        QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("Threshold",          QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("CableExprRPN",       QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("CableExprFull",      QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("AuthLevel",          QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("DisplayID",          QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("DisplayFormat",      QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ChannelID",          QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ControlStep",        QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ControlParam",       QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ControlExprRPN",     QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("ControlExprFull",    QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("States",             QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("OnControlAction",    QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("DispExprRPN",        QString((char*)sqlite3_column_text(statement, i++)));
        control->SetValue("DispExprFull",       QString((char*)sqlite3_column_text(statement, i++)));
                           
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
    if ( e->Track != MainTrackAID->GetNumber() ) {
      continue;
    }

    controlPair = new ControlSignalPair(e->ID, e->Type, e, NULL);
    controlPairs << controlPair;
  }

  for ( i = 0; i < n; i++ ){
    e = controls[i];
    if ( e->Track != MainTrackBID->GetNumber() ) {
      continue;
    }
    controlPair = FindPairByID(e->ID, e->Type);
    if ( NULL == controlPair ) {
      controlPair = new ControlSignalPair(e->ID, e->Type, NULL, e);
      controlPairs << controlPair;
      continue;
    }
    controlPair->AddTrackBSignal(e);
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
 * Function : GetTrackACount
 *****************************************************************************/
int
ControlInformation::GetTrackACount(void)
{
  return GetTrackCount(MainTrackAID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrackBCount
 *****************************************************************************/
int
ControlInformation::GetTrackBCount(void)
{
  return GetTrackCount(MainTrackBID->GetNumber());
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
 * Function : GetTrackAMissingCount
 *****************************************************************************/
int
ControlInformation::GetTrackAMissingCount(void)
{
  ControlSignalPair*                    ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    ep = controlPairs[i];
    if ( ep->GetTrackA() == NULL ) {
      count++;
    }
  }
  return count;  
}

/*****************************************************************************!
 * Function : GetTrackBMissingCount
 *****************************************************************************/
int
ControlInformation::GetTrackBMissingCount(void)
{
  ControlSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    ep = controlPairs[i];
    if ( ep->GetTrackB() == NULL ) {
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

/*****************************************************************************!
 * Function : GetTrackDifferCount
 *****************************************************************************/
void
ControlInformation::GetTrackDifferCount
(int &InSignalMajorCount, int &InMajorCount, int &InSignalMinorCount, int &InMinorCount)
{
  int                                   pairMinor;
  int                                   pairMajor;
  ControlSignalPair*                    ep;
  int                                   i;
  int                                   n;
  QList<ElementDisplayLineFormat*>      formats;
  int                                   signalMajor;
  int                                   signalMinor;

  signalMajor = 0;
  signalMinor = 0;
  InMajorCount = 0;
  InMinorCount = 0;
  formats = MainConfiguration->GetElementLineFormats("Control");

  n = controlPairs.size();
  for (i = 0; i < n; i++) {
    ep = controlPairs[i];
    pairMajor = 0;
    pairMinor = 0;
    ep->GetDifferCounts(pairMajor, pairMinor, formats);
    if ( pairMajor > 0 ) {
      signalMajor++;
    }
    if ( pairMinor > 0 ) {
      signalMinor++;
    }
    InMajorCount += pairMajor;
    InMinorCount += pairMinor;
  }
  InSignalMajorCount = signalMajor;
  InSignalMinorCount = signalMinor;
}

