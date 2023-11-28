/*****************************************************************************
 * FILE NAME    : SignalDisplayWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _signaldisplaywindow_h_
#define _signaldisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalStatsWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SIGNAL_DISPLAY_WINDOW_X         200
#define SIGNAL_DISPLAY_WINDOW_Y         200
#define SIGNAL_DISPLAY_WINDOW_WIDTH     200
#define SIGNAL_DISPLAY_WINDOW_HEIGHT    200

/*****************************************************************************!
 * Exported Class : SignalDisplayWindow
 *****************************************************************************/
class SignalDisplayWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SignalDisplayWindow           (QString InText);

 //! Destructor
 public :
  ~SignalDisplayWindow          ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Protected Data
 protected :
  SignalStatsWindow*            statsWindow;

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();

 //! Private Data
 private :
  QString                       text;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _signaldisplaywindow_h_*/
