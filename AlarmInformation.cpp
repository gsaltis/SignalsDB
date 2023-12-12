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
    if ( e->Track != 2 ) {
      continue;
    }

    alarmPair = new AlarmSignalPair(e->ID, e->Type, e, NULL);
    alarmPairs << alarmPair;
  }

  for ( i = 0; i < n; i++ ){
    e = alarms[i];
    if ( e->Track != 3 ) {
      continue;
    }
    alarmPair = FindPairByID(e->ID, e->Type);
    if ( NULL == alarmPair ) {
      alarmPair = new AlarmSignalPair(e->ID, e->Type, NULL, e);
      alarmPairs << alarmPair;
      continue;
    }
    alarmPair->AddTrack3Signal(e);
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
 * Function : GetTrack2Count
 *****************************************************************************/
int
AlarmInformation::GetTrack2Count(void)
{
  return GetTrackCount(2);
}

/*****************************************************************************!
 * Function : GetTrack3Count
 *****************************************************************************/
int
AlarmInformation::GetTrack3Count(void)
{
  return GetTrackCount(3);
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
 * Function : GetTrack2MissingCount
 *****************************************************************************/
int
AlarmInformation::GetTrack2MissingCount(void)
{
  AlarmSignalPair*                    ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    ep = alarmPairs[i];
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
AlarmInformation::GetTrack3MissingCount(void)
{
  AlarmSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    ep = alarmPairs[i];
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
AlarmInformation::GetTrackDifferCount(void)
{
  AlarmSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = alarmPairs.size();
  for (i = 0; i < n; i++) {
    ep = alarmPairs[i];
    if ( ep->Differ() ) {
      count++;
    }
  }
  return count;
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
