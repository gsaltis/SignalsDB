/*****************************************************************************
 * FILE NAME    : SampleDisplayWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sampledisplaywindow_h_
#define _sampledisplaywindow_h_

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
#define SAMPLE_DISPLAY_WINDOW_X         200
#define SAMPLE_DISPLAY_WINDOW_Y         200
#define SAMPLE_DISPLAY_WINDOW_WIDTH     200
#define SAMPLE_DISPLAY_WINDOW_HEIGHT    200

/*****************************************************************************!
 * Exported Class : SampleDisplayWindow
 *****************************************************************************/
class SampleDisplayWindow : public SignalDisplayWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  SampleDisplayWindow           (QString InText);

 //! Destructor
 public :
  ~SampleDisplayWindow          ();

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

#endif /* _sampledisplaywindow_h_*/
