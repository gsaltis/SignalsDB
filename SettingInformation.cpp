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
#include "main.h"

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
                         "SettingName,"         // 3
                         "ResourceID,"          // 4
                         "Unit,"                // 5
                         "SamplerIndex,"        // 6
                         "SamplerChannel,"      // 7
                         "ValueType,"           // 8
                         "Defaults,"            // 9
                         "Range,"               // 10
                         "DisplayAttr,"         // 11
                         "SetAttr,"             // 12
                         "SetExprRPN,"          // 13
                         "SetExprFull,"         // 14
                         "AuthLevel,"           // 15
                         "DisplayID,"           // 16
                         "DisplayFormat,"       // 17
                         "ChannelID,"           // 18
                         "ControlStep,"         // 19
                         "ControlExprRPN,"      // 20
                         "ControlExprFull,"     // 21
                         "PersistentFlag,"      // 22
                         "OnControlAction,"     // 23
                         "DisplayExprRPN,"      // 24
                         "DisplayExprFull,"     // 25
                         "States "              // 26
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
        setting->SetValue("SettingName", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("ResourceID", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("Unit", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("SamplerIndex", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("SamplerChannel", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("ValueType", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("Defaults", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("Range", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("DisplayAttr", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("SetAttr", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("SetExprRPN", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("SetExprFull", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("AuthLevel", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("DisplayID", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("DisplayFormat", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("ChannelID", 		QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("ControlStep", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("ControlExprRPN", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("ControlExprFull", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("PersistentFlag", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("OnControlAction", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("DisplayExprRPN", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("DisplayExprFull", 	QString((char*)sqlite3_column_text(statement, i++)));
        setting->SetValue("States", 		QString((char*)sqlite3_column_text(statement, i++)));
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
    if ( e->Track != MainTrackAID->GetNumber() ) {
      continue;
    }

    settingPair = new SettingSignalPair(e->ID, e->Type, e, NULL);
    settingPairs << settingPair;
  }

  for ( i = 0; i < n; i++ ){
    e = settings[i]; 
    if ( e->Track != MainTrackBID->GetNumber() ) {
      continue;
    }
    settingPair = FindPairByID(e->ID, e->Type);
    if ( NULL == settingPair ) {
      settingPair = new SettingSignalPair(e->ID, e->Type, NULL, e);
      settingPairs << settingPair;
      continue;
    }
    settingPair->AddTrackBSignal(e);
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
 * Function : GetTrackACount
 *****************************************************************************/
int
SettingInformation::GetTrackACount(void)
{
  return GetTrackCount(MainTrackAID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrackBCount
 *****************************************************************************/
int
SettingInformation::GetTrackBCount(void)
{
  return GetTrackCount(MainTrackBID->GetNumber());
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
 * Function : GetTrackAMissingCount
 *****************************************************************************/
int
SettingInformation::GetTrackAMissingCount(void)
{
  SettingSignalPair*                    ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    ep = settingPairs[i];
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
SettingInformation::GetTrackBMissingCount(void)
{
  SettingSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    ep = settingPairs[i];
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

/*****************************************************************************!
 * Function : GetTrackDifferCount
 *****************************************************************************/
void
SettingInformation::GetTrackDifferCount
(int &InSignalMajorCount, int &InMajorCount, int &InSignalMinorCount, int &InMinorCount)
{
  int                                   pairMinor;
  int                                   pairMajor;
  SettingSignalPair*                    ep;
  int                                   i;
  int                                   n;
  QList<ElementDisplayLineFormat*>      formats;
  int                                   signalMajor;
  int                                   signalMinor;

  signalMajor = 0;
  signalMinor = 0;
  InMajorCount = 0;
  InMinorCount = 0;
  formats = MainConfiguration->GetElementLineFormats("Settings");

  n = settingPairs.size();
  for (i = 0; i < n; i++) {
    ep = settingPairs[i];
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

