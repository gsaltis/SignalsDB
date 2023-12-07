/*****************************************************************************
 * FILE NAME    : AlarmDisplayForm.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _alarmdisplayform_h_
#define _alarmdisplayform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalDisplayForm.h"
#include "NavigationWindow.h"
#include "AlarmInformation.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define ALARM_DISPLAY_FORM_X        200
#define ALARM_DISPLAY_FORM_Y        200
#define ALARM_DISPLAY_FORM_WIDTH    200
#define ALARM_DISPLAY_FORM_HEIGHT   200

/*****************************************************************************!
 * Exported Class : AlarmDisplayForm
 *****************************************************************************/
class AlarmDisplayForm : public SignalDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  AlarmDisplayForm          ();

 //! Destructor
 public :
  ~AlarmDisplayForm         ();

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
  void                          CreateConnections       (void);
  void                          SetTrackInformation     (AlarmSignalPair* InPair);

 //! Private Data
 private :
  NavigationWindow*             navigationWindow;
  AlarmInformation*             alarmInformation;
  QLabel*                       AlarmIDLabel;
  int                           currentEquipIndex;
  QLabel*                       Track3Label;
  QLabel*                       SignalIDLabel;

 //! Public Slots
 public slots :
  void                          SlotNextElement         (void);
  void                          SlotPreviousElement     (void);
  void                          SlotNextDifferElement   (void);
  void                          SlotPrevDifferElement   (void);
  
 //! Public Signals
 signals :
  void                          SignalSetCurrentAlarmIndex (int InCurrentAlarmIndex);

 //! Public Actions
 public :

};

#endif /* _alarmdisplayform_h_*/
