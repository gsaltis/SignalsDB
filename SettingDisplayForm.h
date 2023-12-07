/*****************************************************************************
 * FILE NAME    : SettingDisplayForm.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _settingdisplayform_h_
#define _settingdisplayform_h_

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
#include "SettingInformation.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SETTING_DISPLAY_FORM_X        200
#define SETTING_DISPLAY_FORM_Y        200
#define SETTING_DISPLAY_FORM_WIDTH    200
#define SETTING_DISPLAY_FORM_HEIGHT   200

/*****************************************************************************!
 * Exported Class : SettingDisplayForm
 *****************************************************************************/
class SettingDisplayForm : public SignalDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  SettingDisplayForm          ();

 //! Destructor
 public :
  ~SettingDisplayForm         ();

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
  void                          SetTrackInformation     (SettingSignalPair* InPair);

 //! Private Data
 private :
  NavigationWindow*             navigationWindow;
  SettingInformation*           settingInformation;
  QLabel*                       SettingIDLabel;
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
  void                          SignalSetCurrentSettingIndex (int InCurrentSettingIndex);

 //! Public Actions
 public :

};

#endif /* _settingdisplayform_h_*/
