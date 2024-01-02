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

QList<int>
GetTrackVersions
();

void
ListTrackVersions
();

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
sqlite3*
MainDB = NULL;

QString
MainDBFilename = "Signals.db";

QString
MainOrginzationName = "Vertiv";

QString
MainApplicationName = "SignalsDB";

MainConfig*
MainConfiguration;

bool
MainCreateSummary = false;

TrackNumber*
MainTrackAID = NULL;

TrackNumber*
MainTrackBID = NULL;

bool
MainListTrackVersions = false;

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  int                                   n;
  QString                               filename;
  int                                   initialTab;
  QApplication 				application(argc, argv);
  MainWindow* 				w;
  QPoint                                position;
  QSize                                 size;
  QCommandLineParser                    commandLineParser;

  MainTrackAID = new TrackNumber(20221);
  MainTrackBID = new TrackNumber(30224);
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

  QCommandLineOption                    ConfigListVerssion(QStringList() << "L" << "listversion",
                                                           QString("List available track versions"));

  QCommandLineOption                    ConfigTrackAVersionOption(QStringList() << "A" << "TrackA",
                                                                  QString("Specify the Track A Version"),
                                                                  QString("Version"));
  

  QCommandLineOption                    ConfigTrackBVersionOption(QStringList() << "B" << "TrackB",
                                                                  QString("Specify the Track B Version"),
                                                                  QString("Version"));

  commandLineParser.addOption(InitWindowOption);
  commandLineParser.addOption(ConfigFilenameOption);
  commandLineParser.addOption(ConfigSummaryOption);
  commandLineParser.addOption(ConfigTrackAVersionOption);
  commandLineParser.addOption(ConfigTrackBVersionOption);
  commandLineParser.addOption(ConfigListVerssion);

  //!
  commandLineParser.process(application);
  TRACE_COMMAND_CLEAR();
  initialTab = commandLineParser.value(InitWindowOption).toInt();

  n = commandLineParser.value(ConfigTrackAVersionOption).toInt();
  TRACE_FUNCTION_INT(n);
  if ( n > 0 ) {
    MainTrackAID->SetNumber(n);
  }

  MainListTrackVersions = commandLineParser.isSet(ConfigListVerssion);
  
  n = commandLineParser.value(ConfigTrackBVersionOption).toInt();
  TRACE_FUNCTION_INT(n);
  if ( n > 0 ) {
    MainTrackBID->SetNumber(n);
  }

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
  QList<int>                            trackVersions;
  
  MainOpenDB();

  if ( MainListTrackVersions ) {
    ListTrackVersions();
    exit(EXIT_SUCCESS);
  }
  
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

  trackVersions = GetTrackVersions();
  if ( !trackVersions.contains(MainTrackAID->GetNumber()) ) {
    QMessageBox box = QMessageBox(QMessageBox::Critical,
                                  "Invalid Track A Version",
                                  QString("Track version %1 is not a valid version\n").arg(MainTrackAID->GetNumber()),
                                  QMessageBox::Ok);
    box.exec();
    exit(EXIT_FAILURE);
  }
      
  if ( !trackVersions.contains(MainTrackBID->GetNumber()) ) {
    QMessageBox box = QMessageBox(QMessageBox::Critical,
                                  "Invalid Track B Version",
                                  QString("Track version %1 is not a valid version\n").arg(MainTrackBID->GetNumber()),
                                  QMessageBox::Ok);
    box.exec();
    exit(EXIT_FAILURE);
  }
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

/*****************************************************************************!
 * Function : GetTrackVersions
 *****************************************************************************/
QList<int>
GetTrackVersions
()
{
  sqlite3_stmt*                         statement;
  bool                                  finished;
  QString                               sqlStatement;
  int                                   n;
  QList<int>                            trackVersions;

  sqlStatement = QString("SELECT DISTINCT(Track) FROM Equipment;");
  
  n = sqlite3_prepare_v2(MainDB, sqlStatement.toStdString().c_str(), sqlStatement.length(), &statement, NULL);
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
        trackVersions << sqlite3_column_int(statement, 0);
        break;
      }
      
      case SQLITE_ERROR : {
        finished = true;
        break;
      }
      
      case SQLITE_MISUSE : {
        finished = true;
        break;
      }
    }
  }
  sqlite3_finalize(statement);
  return trackVersions;
}

/*****************************************************************************!
 * Function : ListTrackVersions
 *****************************************************************************/
void
ListTrackVersions
()
{
  int                                   version;
  int                                   i;
  int                                   n;
  QString                               versionStrings;
  QList<int>                            versions;

  versions = GetTrackVersions();

  versionStrings = "Valid Track Versions : \n";
  n = versions.length();
  for (i = 0; i < n; i++) {
    version = versions[i];
    versionStrings += QString("  %1").arg(version);
    if ( i + 1 < n ) {
      versionStrings += QString("\n");
    }
  }

  QMessageBox box = QMessageBox(QMessageBox::Critical,
                                "Track Versions",
                                versionStrings,
                                QMessageBox::Ok);
  box.exec();
}
  
