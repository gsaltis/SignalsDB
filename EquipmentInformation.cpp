/*****************************************************************************
 * FILE NAME    : EquipmentInformation.cpp
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "EquipmentInformation.h"
#include "MainConfig.h"

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

  
  sqlStatement = QString("SELECT Track, Eq, Type, Name, TypeName, GroupName, NumofSamples, NumofCtrl, NumofSet, NumofAlarm, Related FROM Equipment;");

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
        equip->SetID(sqlite3_column_int(statement, 1));
        equip->SetType(sqlite3_column_int(statement, 2));
        equip->SetName((char*)sqlite3_column_text(statement, 3));
        
        equip->TypeName         = (char*)sqlite3_column_text(statement, 4);
        equip->GroupName	= (char*)sqlite3_column_text(statement, 5);
        equip->NumofSamples	= (char*)sqlite3_column_text(statement, 6);
        equip->NumofCtrl	= (char*)sqlite3_column_text(statement, 7);
        equip->NumofSet	        = (char*)sqlite3_column_text(statement, 8);
        equip->NumofAlarm	= (char*)sqlite3_column_text(statement, 9);
        equip->Related          = (char*)sqlite3_column_text(statement, 10);
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
