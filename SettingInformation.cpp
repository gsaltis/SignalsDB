/*****************************************************************************
 * FILE NAME    : SettingInformation.cpp
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
#include "SettingInformation.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : SettingInformation
 *****************************************************************************/
SettingInformation::SettingInformation
() : SignalsInformation()
{
}

/*****************************************************************************!
 * Function : ~SettingInformation
 *****************************************************************************/
SettingInformation::~SettingInformation
()
{
}

/*****************************************************************************!
 * Function : AddSetting
 *****************************************************************************/
void
SettingInformation::AddSetting
(NCUSettingSignal* InSetting)
{
  if ( NULL == InSetting ) {
    return;
  }
  settings << InSetting;
}

/*****************************************************************************!
 * Function : FindSettingByID
 *****************************************************************************/
NCUSettingSignal*
SettingInformation::FindSettingByID
(int InTrack, int InID)
{
  for ( auto i : settings ) {
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
SettingInformation::SQLRead
(sqlite3* InDatabase)
{
  NCUSettingSignal*                     setting;
  bool                                  finished;
  int                                   n;
  sqlite3_stmt*                         statement;
  QString                               sqlStatement;
  QString                               s;
  int                                   i;
  
  sqlStatement = QString("SELECT "
                         "Track,"               // 0
                         "Eq,"                  // 1
                         "SID,"                 // 2
                         "SETName,"             // 3
                         "Unit,"                // 4
                         "SIndx,"               // 5
                         "SChan,"               // 6
                         "ValType,"             // 7
                         "Def,"                 // 8
                         "Range,"               // 9
                         "DisplayAttr,"         // 10
                         "SetAttr,"             // 11
                         "SetExpRPN,"           // 12
                         "SetExpFull,"          // 13
                         "Auth,"                // 14
                         "DisplayID,"           // 15
                         "DispFmt,"             // 16
                         "ChID,"                // 17
                         "Step,"                // 18
                         "CExpRPN,"             // 19
                         "CExpFull,"            // 20
                         "Persist,"             // 21
                         "DispExpRPN,"          // 22
                         "DispExpFull,"         // 23
                         "States,"              // 24
                         "OnCtrl "              // 25
                         "FROM Settings ORDER by CAST(Eq AS INTEGER), CAST(SID AS INTEGER), Track;");

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
        setting = new NCUSettingSignal();
        setting->SetTrack(sqlite3_column_int(statement, 0));

        s = QString((char*)sqlite3_column_text(statement, 1));
        setting->SetID(s.toInt());
        
        s = QString((char*)sqlite3_column_text(statement, 2));
        setting->SetType(s.toInt());

        //!
        i = 3;
        setting->SETName = QString((char*)sqlite3_column_text(statement, i++));
        setting->Unit = QString((char*)sqlite3_column_text(statement, i++));
        setting->SIndx = QString((char*)sqlite3_column_text(statement, i++));
        setting->SChan = QString((char*)sqlite3_column_text(statement, i++));
        setting->ValType = QString((char*)sqlite3_column_text(statement, i++));
        setting->Def = QString((char*)sqlite3_column_text(statement, i++));
        setting->Range = QString((char*)sqlite3_column_text(statement, i++));
        setting->DisplayAttr = QString((char*)sqlite3_column_text(statement, i++));
        setting->SetAttr = QString((char*)sqlite3_column_text(statement, i++));
        setting->SetExpRPN = QString((char*)sqlite3_column_text(statement, i++));
        setting->SetExpFull = QString((char*)sqlite3_column_text(statement, i++));
        setting->Auth = QString((char*)sqlite3_column_text(statement, i++));
        setting->DisplayID = QString((char*)sqlite3_column_text(statement, i++));
        setting->DispFmt = QString((char*)sqlite3_column_text(statement, i++));
        setting->ChID = QString((char*)sqlite3_column_text(statement, i++));
        setting->Step = QString((char*)sqlite3_column_text(statement, i++));
        setting->CExpRPN = QString((char*)sqlite3_column_text(statement, i++));
        setting->CExpFull = QString((char*)sqlite3_column_text(statement, i++));
        setting->Persist = QString((char*)sqlite3_column_text(statement, i++));
        setting->DispExpRPN = QString((char*)sqlite3_column_text(statement, i++));
        setting->DispExpFull = QString((char*)sqlite3_column_text(statement, i++));
        setting->States = QString((char*)sqlite3_column_text(statement, i++));
        setting->OnCtrl = QString((char*)sqlite3_column_text(statement, i++));
        settings << setting;
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
SettingInformation::GetCountByTrack
(int InTrack)
{
  int                                   n;

  n = 0;

  for ( auto i : settings ) {
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
SettingInformation::CreatePairs(void)
{
  SettingSignalPair*                    settingPair;
  NCUSettingSignal*                     e;
  int                                   i;
  int                                   n;

  n = settings.size();
  for (i = 0; i < n; i++) {
    e = settings[i];
    if ( e->Track != 2 ) {
      continue;
    }

    settingPair = new SettingSignalPair(e->ID, e->Type, e, NULL);
    settingPairs << settingPair;
  }

  for ( i = 0; i < n; i++ ){
    e = settings[i];
    if ( e->Track != 3 ) {
      continue;
    }
    settingPair = FindPairByID(e->ID, e->Type);
    if ( NULL == settingPair ) {
      settingPair = new SettingSignalPair(e->ID, e->Type, NULL, e);
      settingPairs << settingPair;
      continue;
    }
    settingPair->AddTrack3Signal(e);
  }
}

/*****************************************************************************!
 * Function : FindPairByID
 *****************************************************************************/
SettingSignalPair*
SettingInformation::FindPairByID
(int InID, int InSID)
{
  int                                   i, n;
  SettingSignalPair*                    pair;

  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    pair = settingPairs[i];
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
SettingInformation::GetTrack2Count(void)
{
  return GetTrackCount(2);
}

/*****************************************************************************!
 * Function : GetTrack3Count
 *****************************************************************************/
int
SettingInformation::GetTrack3Count(void)
{
  return GetTrackCount(3);
}

/*****************************************************************************!
 * Function : GetTrackCount
 *****************************************************************************/
int
SettingInformation::GetTrackCount
(int InTrack)
{
  int                                   count;
  int                                   i;
  int                                   n;
  NCUSettingSignal*                     e;

  count = 0;
  n = settings.size();
  for (i = 0; i < n; i++) {
    e = settings[i];

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
SettingInformation::GetTrack2MissingCount(void)
{
  SettingSignalPair*                    ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    ep = settingPairs[i];
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
SettingInformation::GetTrack3MissingCount(void)
{
  SettingSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    ep = settingPairs[i];
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
SettingInformation::GetTrackDifferCount(void)
{
  SettingSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    ep = settingPairs[i];
    if ( ep->Differ() ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetPairByIndex
 *****************************************************************************/
SettingSignalPair*
SettingInformation::GetPairByIndex
(int InIndex)
{
  if ( InIndex >= settingPairs.size() ) {
    return NULL;
  }
  return settingPairs[InIndex];
}

/*****************************************************************************!
 * Function : GetPairCount
 *****************************************************************************/
int
SettingInformation::GetPairCount
()
{
  return settingPairs.size();
}
