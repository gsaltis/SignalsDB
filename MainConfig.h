/*****************************************************************************
 * FILE NAME    : MainConfig.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _mainconfig_h_
#define _mainconfig_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "sqlite3.h"
#include "EquipmentInformation.h"
#include "ControlInformation.h"
#include "AlarmInformation.h"
#include "SettingInformation.h"
#include "SampleInformation.h"
#include "ElementDisplayLineFormat.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : MainConfig
 *****************************************************************************/
class MainConfig : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  MainConfig                    ();

 //! Destructor
 public :
  ~MainConfig                   ();

 //! Public Methods
 public :
  void                          ReadElementLineFormats  (void);
  static int                    ReadElementLineFormatsCB (void* InPointer, int InColumnCounts, char** InColumnValues, char** InColumnNames);
  void                          AddElementDisplayLineFormat (QString InSignalTypeName, ElementDisplayLineFormat* InFormat);
  QList<ElementDisplayLineFormat*> GetElementLineFormats (QString InSignalTypeName);
  static void                   CreateSummaryFile       (void);
  
 //! Public Data
 public :
  static sqlite3*                       database;
  static EquipmentInformation*          equipmentInformation;
  static ControlInformation*            controlInformation;
  static AlarmInformation*              alarmInformation;
  static SettingInformation*            settingInformation;
  static SampleInformation*             sampleInformation;

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  QHash<QString, QList<ElementDisplayLineFormat*>>      formats;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _mainconfig_h_*/
