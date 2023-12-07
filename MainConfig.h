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

 //! Public Data
 public :
  static sqlite3*                       database;
  static EquipmentInformation*          equipmentInformation;
  static ControlInformation*            controlInformation;
  static AlarmInformation*              alarmInformation;
  
 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _mainconfig_h_*/
