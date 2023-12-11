/*****************************************************************************
 * FILE NAME    : MainConfig.cpp
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
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
sqlite3*
MainConfig::database = NULL;

EquipmentInformation*
MainConfig::equipmentInformation = NULL;

ControlInformation*
MainConfig::controlInformation = NULL;

AlarmInformation*
MainConfig::alarmInformation = NULL;

SettingInformation*
MainConfig::settingInformation = NULL;

SampleInformation*
MainConfig::sampleInformation = NULL;

/*****************************************************************************!
 * Function : MainConfig
 *****************************************************************************/
MainConfig::MainConfig
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~MainConfig
 *****************************************************************************/
MainConfig::~MainConfig
()
{
}

/*****************************************************************************!
 * Function : ReadElementLineFormats
 *****************************************************************************/
void
MainConfig::ReadElementLineFormats(void)
{
  int                                   n;
  QString                               selectStatement;

  selectStatement = QString("SELECT * from ElementDisplay ORDER By SignalTypeName, LineOrder;");
  n = sqlite3_exec(MainDB, selectStatement.toStdString().c_str(), MainConfig::ReadElementLineFormatsCB, this, NULL);
  if ( n != SQLITE_OK ) {
    QMessageBox box = QMessageBox(QMessageBox::Critical,
                                  "sqlite3_exec Fail",
                                  QString("sqlite3_exec() FAIL\n"
                                          "%1 : %2\n"
                                          "%3\n"
                                          "%4")
                                  .arg(__FILE__).arg(__LINE__)
                                  .arg(selectStatement)
                                  .arg(sqlite3_errstr(n)));
    box.exec();
    exit(EXIT_FAILURE);
  }
}


/*****************************************************************************!
 * Function : ReadElementLineFormatsCB
 *****************************************************************************/
int
MainConfig::ReadElementLineFormatsCB
(void* InPointer, int InColumnCounts, char** InColumnValues, char** InColumnNames)
{
  QString                               signalTypeName;
  ElementDisplayLineFormat*             format;
  QString                               columnName;
  QString                               columnValue;
  int                                   i;
  MainConfig*                           thisPointer;

  thisPointer = (MainConfig*)InPointer;

  format = new ElementDisplayLineFormat();

  for (i = 0; i < InColumnCounts; i++) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "SignalTypeName" ) {
      format->SetSignalTypeName(columnValue);
      signalTypeName = columnValue;
      continue;
    }
    if ( columnName == "LineOrder" ) {
      format->SetLineOrder(atoi(columnValue.toStdString().c_str()));
      continue;
    }
    if ( columnName == "ElementKey" ) {
      format->SetElementKey(columnValue);
      continue;
    }
    if ( columnName == "ElementName" ) {
      format->SetElementName(columnValue);
      continue;
    }
    if ( columnName == "DifferenceSeverity" ) {
      format->SetDifferenceSeverity(columnValue);
      continue;
    }
    if ( columnName == "LineHeightMultiplier" ) {
      format->SetLineHeightMultiplier(atoi(columnValue.toStdString().c_str()));
      continue;
    }
  }
  thisPointer->AddElementDisplayLineFormat(signalTypeName, format);
  return 0;
}

/*****************************************************************************!
 * Function : AddElementDisplayLineFormat
 *****************************************************************************/
void
MainConfig::AddElementDisplayLineFormat
(QString InSignalTypeName, ElementDisplayLineFormat* InFormat)
{
  QList<ElementDisplayLineFormat*>              lineFormats;

  lineFormats = formats[InSignalTypeName];
  lineFormats << InFormat;
  formats[InSignalTypeName] = lineFormats;
}

/*****************************************************************************!
 * Function : GetElementLineFormats
 *****************************************************************************/
QList<ElementDisplayLineFormat*>
MainConfig::GetElementLineFormats
(QString InSignalTypeName)
{
  return formats[InSignalTypeName];
}
