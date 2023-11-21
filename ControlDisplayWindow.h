/*****************************************************************************
 * FILE NAME    : ControlDisplayWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _controldisplaywindow_h_
#define _controldisplaywindow_h_

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
#define CONTROL_DISPLAY_WINDOW_X        200
#define CONTROL_DISPLAY_WINDOW_Y        200
#define CONTROL_DISPLAY_WINDOW_WIDTH    200
#define CONTROL_DISPLAY_WINDOW_HEIGHT   200

/*****************************************************************************!
 * Exported Class : ControlDisplayWindow
 *****************************************************************************/
class ControlDisplayWindow : public SignalDisplayWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  ControlDisplayWindow          (QString InText);

 //! Destructor
 public :
  ~ControlDisplayWindow         ();

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

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _controldisplaywindow_h_*/
