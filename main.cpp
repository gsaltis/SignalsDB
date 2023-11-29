/*****************************************************************************
 FILE NAME      : main.cpp
 DATE           : November 21 2023
 PROJECT        : Signals Database
 COPYRIGHT      : Copyright (C) 2023 by Gregory R Saltis
******************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtGui>
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "MainConfig.h"
#include "main.h"
#include "sqlite3.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
void
MainOpenDB
();

void
Initialize
();

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
sqlite3*
MainDB = NULL;

QString
MainDBFilename = "Config.db";
  
/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  QApplication 				application(argc, argv);
  MainWindow* 				w;

  Initialize();
  application.setApplicationName("SignalsDatabase");
  application.setApplicationVersion("0.0.0");
  application.setOrganizationName("Greg Saltis");
  application.setOrganizationDomain("www.gsaltis.com");
  
  w = new MainWindow(NULL);
  w->resize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
  w->move(1980, MAIN_WINDOW_Y);
  w->show();
  
  return application.exec();
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
Initialize
()
{
  MainOpenDB();
  MainConfig::equipmentInformation = new EquipmentInformation();
  MainConfig::equipmentInformation->SQLRead(MainConfig::database);
}

/*****************************************************************************!
 * Function : MainOpenDB
 *****************************************************************************/
void
MainOpenDB
()
{
  int                                   n;
  n = sqlite3_open(MainDBFilename.toStdString().c_str(), &MainDB);
  if ( n != SQLITE_OK ) {
    QMessageBox box = QMessageBox(QMessageBox::Critical,
                                  "sqlite3_open() Fail",
                                  QString("sqlite3_open() Fail\n%1 %2\n%3").arg(__FILE__).arg(__LINE__).
                                  arg(sqlite3_errstr(n)),
                                  QMessageBox::Ok);
    box.exec();
    exit(EXIT_FAILURE);
  }
  MainConfig::database = MainDB;
}
