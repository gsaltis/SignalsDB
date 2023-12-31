/*****************************************************************************
 * FILE NAME    : EquipmentInformation.cpp
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "EquipmentInformation.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : EquipmentInformation
 *****************************************************************************/
EquipmentInformation::EquipmentInformation
() : SignalsInformation()
{
}

/*****************************************************************************!
 * Function : ~EquipmentInformation
 *****************************************************************************/
EquipmentInformation::~EquipmentInformation
()
{
}

/*****************************************************************************!
 * Function : AddEquipment
 *****************************************************************************/
void
EquipmentInformation::AddEquipment
(NCUEquipment* InEquipment)
{
  if ( NULL == InEquipment ) {
    return;
  }
  equipment << InEquipment;
}

/*****************************************************************************!
 * Function : FindEquipmentByID
 *****************************************************************************/
NCUEquipment*
EquipmentInformation::FindEquipmentByID
(int InTrack, int InID)
{
  for ( auto i : equipment ) {
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
EquipmentInformation::SQLRead
(sqlite3* InDatabase)
{
  NCUEquipment*                         equip;
  bool                                  finished;
  int                                   n;
  sqlite3_stmt*                         statement;
  QString                               sqlStatement;
  QString                               s;
  int                                   i;
  
  sqlStatement = QString("SELECT "
                         "Track,"                            // 0
                         "Eq,"                               // 1
                         "Type,"                             // 2
                         "Name,"                             // 3
                         "TypeName,"                         // 4
                         "GroupName,"                        // 5
                         "NumberOfSamples,"                  // 6
                         "NumberOfCtrl,"                     // 7
                         "NumberOfSet,"                      // 8
                         "NumberOfAlarm,"                    // 9
                         "Related "                          // 10
                         "FROM Equipment;");

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
        equip = new NCUEquipment();
        equip->SetTrack(sqlite3_column_int(statement, 0));

        s = QString((char*)sqlite3_column_text(statement, 1));
        equip->SetID(s.toInt());
        
        s = QString((char*)sqlite3_column_text(statement, 2));
        equip->SetType(s.toInt());

        i = 3;
        equip->SetValue("Name", 	(char*)sqlite3_column_text(statement, i++));
        equip->SetValue("TypeName", 	(char*)sqlite3_column_text(statement, i++));
        equip->SetValue("GroupName", 	(char*)sqlite3_column_text(statement, i++));
        equip->SetValue("NumofSamples", (char*)sqlite3_column_text(statement, i++));
        equip->SetValue("NumofCtrl",	(char*)sqlite3_column_text(statement, i++));
        equip->SetValue("NumofSet", 	(char*)sqlite3_column_text(statement, i++));
        equip->SetValue("NumofAlarm", 	(char*)sqlite3_column_text(statement, i++));
        equip->SetValue("Related",	(char*)sqlite3_column_text(statement, i++));
        equipment << equip;
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
EquipmentInformation::GetCountByTrack
(int InTrack)
{
  int                                   n;

  n = 0;

  for ( auto i : equipment ) {
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
EquipmentInformation::CreatePairs(void)
{
  EquipmentSignalPair*                  equipmentPair;
  NCUEquipment*                         e;
  int                                   i;
  int                                   n;

  n = equipment.size();
  for (i = 0; i < n; i++) {
    e = equipment[i];
    if ( e->Track != MainTrackAID->GetNumber() ) {
      continue;
    }

    equipmentPair = new EquipmentSignalPair(e->ID, e, NULL);
    equipmentPairs << equipmentPair;
  }

  for ( i = 0; i < n; i++ ){
    e = equipment[i];
    if ( e->Track != MainTrackBID->GetNumber() ) {
      continue;
    }
    equipmentPair = FindPairByID(e->ID);
    if ( NULL == equipmentPair ) {
      equipmentPair = new EquipmentSignalPair(e->ID, NULL, e);
      equipmentPairs << equipmentPair;
      continue;
    }
    equipmentPair->AddTrackBSignal(e);
  }
}

/*****************************************************************************!
 * Function : FindPairByID
 *****************************************************************************/
EquipmentSignalPair*
EquipmentInformation::FindPairByID
(int InID)
{
  int                                   i, n;
  EquipmentSignalPair*                  pair;

  n = equipmentPairs.size();
  for (i = 0; i < n; i++) {
    pair = equipmentPairs[i];
    if ( pair->GetID() == InID ) {
      return pair;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetTrack2Count
 *****************************************************************************/
int
EquipmentInformation::GetTrack2Count(void)
{
  return GetTrackCount(MainTrackAID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrack3Count
 *****************************************************************************/
int
EquipmentInformation::GetTrack3Count(void)
{
  return GetTrackCount(MainTrackBID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrackCount
 *****************************************************************************/
int
EquipmentInformation::GetTrackCount
(int InTrack)
{
  int                           count;
  int                           i;
  int                           n;
  NCUEquipment*                 e;

  count = 0;
  n = equipment.size();
  for (i = 0; i < n; i++) {
    e = equipment[i];

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
EquipmentInformation::GetTrack2MissingCount(void)
{
  EquipmentSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = equipmentPairs.size();
  for (i = 0; i < n; i++) {
    ep = equipmentPairs[i];
    if ( ep->GetTrackA() == NULL ) {
      count++;
    }
  }
  return count;  
}

/*****************************************************************************!
 * Function : GetTrack3MissingCount
 *****************************************************************************/
int
EquipmentInformation::GetTrack3MissingCount(void)
{
  EquipmentSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = equipmentPairs.size();
  for (i = 0; i < n; i++) {
    ep = equipmentPairs[i];
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
EquipmentInformation::GetTrackDifferCount(void)
{
  EquipmentSignalPair*                  ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = equipmentPairs.size();
  for (i = 0; i < n; i++) {
    ep = equipmentPairs[i];
    if ( ep->Differ() ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetPairByIndex
 *****************************************************************************/
EquipmentSignalPair*
EquipmentInformation::GetPairByIndex
(int InIndex)
{
  if ( InIndex >= equipmentPairs.size() ) {
    return NULL;
  }
  return equipmentPairs[InIndex];
}

/*****************************************************************************!
 * Function : GetPairCount
 *****************************************************************************/
int
EquipmentInformation::GetPairCount
()
{
  return equipmentPairs.size();
}

/*****************************************************************************!
 * Function : AddSummary
 *****************************************************************************/
void
EquipmentInformation::AddSummary
(FILE* InFile)
{
  int                                   track3Missing;
  int                                   track2Missing;
  int                                   track3Count;
  int                                   track2Count;
  track2Count = GetTrack2Count();
  track3Count = GetTrack3Count();

  track2Missing = GetTrack2MissingCount();
  track3Missing = GetTrack3MissingCount();

  fprintf(InFile,"EQUIPMENT\n");
  fprintf(InFile,"  Track 2 Count :             %d\n", track2Count);
  fprintf(InFile,"  Track 3 Count :             %d\n", track3Count);
  fprintf(InFile,"  Tracks Missing in Track 2 : %d\n", track2Missing);
  fprintf(InFile,"  Tracks Missing in Track s : %d\n", track3Missing);
}
