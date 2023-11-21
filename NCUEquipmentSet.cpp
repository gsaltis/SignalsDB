/*****************************************************************************
 * FILE NAME    : NCUEquipmentSet.cpp
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
#include "NCUEquipmentSet.h"

/*****************************************************************************!
 * Function : NCUEquipmentSet
 *****************************************************************************/
NCUEquipmentSet::NCUEquipmentSet
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~NCUEquipmentSet
 *****************************************************************************/
NCUEquipmentSet::~NCUEquipmentSet
()
{
}

/*****************************************************************************!
 * Function : SQLRead
 *****************************************************************************/
void
NCUEquipmentSet::SQLRead
(sqlite3* InDatabase)
{
  QString                               sqlStatement;
  sqlite3_stmt*                         statement;
  int                                   n;
  
  sqlStatement = "SELECT Track,Eq,Type,Name,TypeName,GroupName,NumofSamples,NumofCtrl,NumofSet,NumofAlarm,Related from Equipment;";

  n = sqlite3_prepare_v2(InDatabase, sqlStatement.toStdString().c_str(), sqlStatement.length(), &statement, NULL);
  if ( n != SQLITE_OK ) {
    QString                             s =
      QString("sqlite3_prepare_v2 Failure\n") + 
      QString("%1:%2\n").arg(__FILE__).arg(__LINE__) +
      QString("%1\n").arg(sqlStatement) +
      QString("%1\n").arg(sqlite3_errstr(n));
    QMessageBox box = QMessageBox(QMessageBox::Critical, "SQLite3 Error", s, QMessageBox::Ok);
    box.exec();
    exit(EXIT_FAILURE);
  }
  
  sqlite3_finalize(statement);
}
