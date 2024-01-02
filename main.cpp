/*****************************************************************************
 FILE NAME      : main.cpp
 DATE           : November 21 2023
 PROJECT        : Signals Database
 COPYRIGHT      : Copyright (C) 2023 by Gregory R Saltis
******************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtGui>
#include <QMessageBox>
#include <QSettings>

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

QString
MainOrginzationName = "Vertiv";

QString
MainApplicationName = "SignalsDB";

MainConfig*
MainConfiguration;

bool
MainCreateSummary = false;

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  QString                               filename;
  int                                   initialTab;
  QApplication 				application(argc, argv);
  MainWindow* 				w;
  QPoint                                position;
  QSize                                 size;
  QCommandLineParser                    commandLineParser;
  
  application.setApplicationName("SignalsDatabase");
  application.setApplicationVersion("0.0.0");
  application.setOrganizationName("Greg Saltis");
  application.setOrganizationDomain("www.gsaltis.com");

  commandLineParser.setApplicationDescription("Signal Database Viewer");
  commandLineParser.addHelpOption();
  commandLineParser.addVersionOption();

  QCommandLineOption                    InitWindowOption(QStringList() << "s" << "signal",
                                                         QString("Select initial signal window"),
                                                         QString("index"));

  QCommandLineOption                    ConfigFilenameOption(QStringList() << "f" << "file",
                                                             QString("Specify the config database filename"),
                                                             QString("filename"));

  QCommandLineOption                    ConfigSummaryOption(QStringList() << "S" << "summary",
                                                            QString("Create a summary file"));
  
  commandLineParser.addOption(InitWindowOption);
  commandLineParser.addOption(ConfigFilenameOption);
  commandLineParser.addOption(ConfigSummaryOption);
  
  commandLineParser.process(application);
  TRACE_COMMAND_CLEAR();
  initialTab = commandLineParser.value(InitWindowOption).toInt();
  
  filename = commandLineParser.value(ConfigFilenameOption);
  if ( !filename.isEmpty() ) {
    MainDBFilename = filename;
  }
  MainCreateSummary = commandLineParser.isSet(ConfigSummaryOption);
  
  Initialize();
  w = new MainWindow(initialTab);
  MainGetMainWindowGeometry(position, size);
  w->resize(size);
  w->move(position);
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

  MainConfig::controlInformation = new ControlInformation();
  MainConfig::controlInformation->SQLRead(MainConfig::database);

  MainConfig::alarmInformation = new AlarmInformation();
  MainConfig::alarmInformation->SQLRead(MainConfig::database);

  MainConfig::settingInformation = new SettingInformation();
  MainConfig::settingInformation->SQLRead(MainConfig::database);

  MainConfig::sampleInformation = new SampleInformation();
  MainConfig::sampleInformation->SQLRead(MainConfig::database);

  if ( MainCreateSummary ) {
    MainConfig::CreateSummaryFile();
  }
  MainConfiguration = new MainConfig();
  MainConfiguration->ReadElementLineFormats();
}

/*****************************************************************************!
 * Function : MainOpenDB
 *****************************************************************************/
void
MainOpenDB
()
{
  int                                   n;

  TRACE_FUNCTION_QSTRING(MainDBFilename);
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

/*****************************************************************************!
 * Function : MainSetMainWindowGeometry
 *****************************************************************************/
void
MainSetMainWindowGeometry
(QPoint InPosition, QSize InSize)
{
  QSettings                             settings(MainOrginzationName, MainApplicationName);

  settings.setValue("MainWindow/X", InPosition.x());
  settings.setValue("MainWindow/Y", InPosition.y());
  settings.setValue("MainWindow/Width", InSize.width());
  settings.setValue("MainWindow/Height", InSize.height());
}

/*****************************************************************************!
 * Function : MainGetMainWidnowGeometry
 *****************************************************************************/
void
MainGetMainWindowGeometry
(QPoint &InPosition, QSize &InSize)
{
  QSettings                             settings(MainOrginzationName, MainApplicationName);
  int                                   x, y, width, height;

  x = settings.value("MainWindow/X", MAIN_WINDOW_X).toInt();
  y = settings.value("MainWindow/Y", MAIN_WINDOW_Y).toInt();
  width = settings.value("MainWindow/Width", MAIN_WINDOW_WIDTH).toInt();
  height = settings.value("MainWindow/Height", MAIN_WINDOW_HEIGHT).toInt();

  InPosition.setX(x);
  InPosition.setY(y);

  InSize.setWidth(width);
  InSize.setHeight(height);
}

  
  
