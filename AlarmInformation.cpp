/*****************************************************************************
 * FILE NAME    : AlarmInformation.cpp
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
#include "AlarmInformation.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : AlarmInformation
 *****************************************************************************/
AlarmInformation::AlarmInformation
() : SignalsInformation()
{
}

/*****************************************************************************!
 * Function : ~AlarmInformation
 *****************************************************************************/
AlarmInformation::~AlarmInformation
()
{
}

/*****************************************************************************!
 * Function : AddAlarm
 *****************************************************************************/
void
AlarmInformation::AddAlarm
(NCUAlarmSignal* InAlarm)
{
  if ( NULL == InAlarm ) {
    return;
  }
  alarms << InAlarm;
}

/*****************************************************************************!
 * Function : FindAlarmByID
 *****************************************************************************/
NCUAlarmSignal*
AlarmInformation::FindAlarmByID
(int InTrack, int InID)
{
  for ( auto i : alarms ) {
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
AlarmInformation::SQLRead
(sqlite3* InDatabase)
{
  int                                   i;
  NCUAlarmSignal*                       alarm;
  bool                                  finished;
  int                                   n;
  sqlite3_stmt*                         statement;
  QString                               sqlStatement;
  QString                               s;
  
  sqlStatement = QString("SELECT "
                         "Track,"               // 0
                         "Eq,"                  // 1
                         "SID,"                 // 2
                         "AlarmName,"           // 3
                         "Level,"               // 4
                         "ExpRPN,"              // 5
                         "EXPFull,"             // 6
                         "Delay,"               // 7
                         "SuppressRPN,"         // 8
                         "SuppressFull,"        // 9
                         "Relay,"               // 10
                         "Help "                // 11
                         "FROM Alarms ORDER by CAST(Eq AS INTEGER), CAST(SID AS INTEGER), Track;");

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
        alarm = new NCUAlarmSignal();
        alarm->SetTrack(sqlite3_column_int(statement, 0));

        s = QString((char*)sqlite3_column_text(statement, 1));
        alarm->SetID(s.toInt());
        
        s = QString((char*)sqlite3_column_text(statement, 2));
        alarm->SetType(s.toInt());

        s = QString((char*)sqlite3_column_text(statement, 1));
        alarm->SetID(s.toInt());
        
        //!
        i = 3;
        alarm->SetValue("AlarmName", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("Level", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("ExpRPN", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("EXPFull", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("Delay", QString((char*)sqlite3_column_text(statement, i++)));

        alarm->SetValue("SuppressRPN", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("SuppressFull", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("Relay", QString((char*)sqlite3_column_text(statement, i++)));
        alarm->SetValue("Help", QString((char*)sqlite3_column_text(statement, i++)));
        alarms << alarm;
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
AlarmInformation::GetCountByTrack
(int InTrack)
{
  int                                   n;

  n = 0;

  for ( auto i : alarms ) {
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
AlarmInformation::CreatePairs(void)
{
  AlarmSignalPair*                    alarmPair;
  NCUAlarmSignal*                     e;
  int                                   i;
  int                                   n;

  n = alarms.size();
  for (i = 0; i < n; i++) {
    e = alarms[i];
    if ( e->Track != MainTrackAID->GetNumber() ) {
      continue;
    }

    alarmPair = new AlarmSignalPair(e->ID, e->Type, e, NULL);
    alarmPairs << alarmPair;
  }

  for ( i = 0; i < n; i++ ){
    e = alarms[i];
    if ( e->Track != MainTrackBID->GetNumber() ) {
      continue;
    }
    alarmPair = FindPairByID(e->ID, e->Type);
    if ( NULL == alarmPair ) {
      alarmPair = new AlarmSignalPair(e->ID, e->Type, NULL, e);
      alarmPairs << alarmPair;
      continue;
    }
    alarmPair->AddTrackBSignal(e);
  }
}

/*****************************************************************************!
 * Function : FindPairByID
 *****************************************************************************/
AlarmSignalPair*
AlarmInformation::FindPairByID
(int InID, int InSID)
{
  int                                   i, n;
  AlarmSignalPair*                    pair;

  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    pair = alarmPairs[i];
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
AlarmInformation::GetTrackACount(void)
{
  return GetTrackCount(MainTrackAID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrackBCount
 *****************************************************************************/
int
AlarmInformation::GetTrackBCount(void)
{
  return GetTrackCount(MainTrackBID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrackCount
 *****************************************************************************/
int
AlarmInformation::GetTrackCount
(int InTrack)
{
  int                                   count;
  int                                   i;
  int                                   n;
  NCUAlarmSignal*                     e;

  count = 0;
  n = alarms.size();
  for (i = 0; i < n; i++) {
    e = alarms[i];

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
AlarmInformation::GetTrackAMissingCount(void)
{
  AlarmSignalPair*                    ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    ep = alarmPairs[i];
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
AlarmInformation::GetTrackBMissingCount(void)
{
  AlarmSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    ep = alarmPairs[i];
    if ( ep->GetTrackB() == NULL ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetTrackDifferCount
 *****************************************************************************/
void
AlarmInformation::GetTrackDifferCount
(int &InSignalMajorCount, int &InMajorCount, int &InSignalMinorCount, int &InMinorCount)
{
  int                                   pairMinor;
  int                                   pairMajor;
  AlarmSignalPair*                      ep;
  int                                   i;
  int                                   n;
  QList<ElementDisplayLineFormat*>      formats;
  int                                   signalMajor;
  int                                   signalMinor;

  signalMajor = 0;
  signalMinor = 0;
  InMajorCount = 0;
  InMinorCount = 0;
  formats = MainConfiguration->GetElementLineFormats("Alarm");

  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    ep = alarmPairs[i];
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

/*****************************************************************************!
 * Function : GetPairByIndex
 *****************************************************************************/
AlarmSignalPair*
AlarmInformation::GetPairByIndex
(int InIndex)
{
  if ( InIndex >= alarmPairs.size() ) {
    return NULL;
  }
  return alarmPairs[InIndex];
}

/*****************************************************************************!
 * Function : GetPairCount
 *****************************************************************************/
int
AlarmInformation::GetPairCount
()
{
  return alarmPairs.size();
}
