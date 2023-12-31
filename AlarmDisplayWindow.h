/*****************************************************************************
 * FILE NAME    : AlarmDisplayWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _alarmdisplaywindow_h_
#define _alarmdisplaywindow_h_

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
#include "AlarmDisplayForm.h"
#include "AlarmInformation.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define ALARM_DISPLAY_WINDOW_X          200
#define ALARM_DISPLAY_WINDOW_Y          200
#define ALARM_DISPLAY_WINDOW_WIDTH      200
#define ALARM_DISPLAY_WINDOW_HEIGHT     200

/*****************************************************************************!
 * Exported Class : AlarmDisplayWindow
 *****************************************************************************/
class AlarmDisplayWindow : public SignalDisplayWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  AlarmDisplayWindow            (QString InText);

 //! Destructor
 public :
  ~AlarmDisplayWindow           ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          resizeEvent             (QResizeEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          SetAlarmInformation     ();
  
 //! Private Data
 private :
  AlarmDisplayForm*             alarmForm;
  AlarmInformation*             alarmInfo;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _alarmdisplaywindow_h_*/
