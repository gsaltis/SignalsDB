/*****************************************************************************
 * FILE NAME    : ControlDisplayForm.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _controldisplayform_h_
#define _controldisplayform_h_

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
#include "ControlInformation.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CONTROL_DISPLAY_FORM_X        200
#define CONTROL_DISPLAY_FORM_Y        200
#define CONTROL_DISPLAY_FORM_WIDTH    200
#define CONTROL_DISPLAY_FORM_HEIGHT   200

/*****************************************************************************!
 * Exported Class : ControlDisplayForm
 *****************************************************************************/
class ControlDisplayForm : public SignalDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  ControlDisplayForm          ();

 //! Destructor
 public :
  ~ControlDisplayForm         ();

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
  void                          SetTrackInformation     (ControlSignalPair* InPair);

 //! Private Data
 private :
  NavigationWindow*             navigationWindow;
  ControlInformation*           controlInformation;
  QLabel*                       ControlIDLabel;
  int                           currentEquipIndex;
  QLabel*                       Track3Label;
  QLabel*                       SignalIDLabel;

 //! Public Slots
 public slots :
  void                          SlotNextElement         (int InMajorMinorFlags);
  void                          SlotPreviousElement     (int InMajorMinorFlags);
  void                          SlotFirstElement        (void);
  void                          SlotLastElement         (void);
  
 //! Public Signals
 signals :
  void                          SignalSetCurrentControlIndex (int InCurrentControlIndex);

 //! Public Actions
 public :

};

#endif /* _controldisplayform_h_*/
