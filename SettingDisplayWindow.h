/*****************************************************************************
 * FILE NAME    : SettingDisplayWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _settingdisplaywindow_h_
#define _settingdisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalDisplayWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SETTING_DISPLAY_WINDOW_X        200
#define SETTING_DISPLAY_WINDOW_Y        200
#define SETTING_DISPLAY_WINDOW_WIDTH    200
#define SETTING_DISPLAY_WINDOW_HEIGHT   200

/*****************************************************************************!
 * Exported Class : SettingDisplayWindow
 *****************************************************************************/
class SettingDisplayWindow : public SignalDisplayWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  SettingDisplayWindow          ();

 //! Destructor
 public :
  ~SettingDisplayWindow         ();

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
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _settingdisplaywindow_h_*/
