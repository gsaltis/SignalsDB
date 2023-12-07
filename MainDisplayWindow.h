/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.h
 * DATE         : November 21 2023
 * PROJECT      : Signals Database
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _maindisplaywindow_h_
#define _maindisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QTabBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalTabWindow.h"
#include "AlarmDisplayWindow.h"
#include "ControlDisplayWindow.h"
#include "EquipmentDisplayWindow.h"
#include "SampleDisplayWindow.h"
#include "SettingDisplayWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : MainDisplayWindow
 *****************************************************************************/
class MainDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  MainDisplayWindow             (int InInitialTab);

 //! Destructor
 public :
  ~MainDisplayWindow            ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          InitializeSubWindows    ();
  void                          CreateSubWindows        ();
  void                          CreateConnections       ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          HideWindows             (void);

 //! Private Data
 private :
  AlarmDisplayWindow*           alarmDisplayWindow;
  ControlDisplayWindow*         controlDisplayWindow;
  EquipmentDisplayWindow*       equipmentDisplayWindow;
  SampleDisplayWindow*          sampleDisplayWindow;
  SettingDisplayWindow*         settingDisplayWindow;
  
  QTabBar*                      tabBar;
  QList<QWidget*>               windows;

 //! Public Slots
 public slots :
  void                          SlotTabSelected         (int InTabIndex);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _maindisplaywindow_h_*/
