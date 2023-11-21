/*****************************************************************************
 * FILE NAME    : SignalTabWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _signaltabwindow_h_
#define _signaltabwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTabWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SIGNAL_TAB_WINDOW_X             200
#define SIGNAL_TAB_WINDOW_Y             200
#define SIGNAL_TAB_WINDOW_WIDTH         200
#define SIGNAL_TAB_WINDOW_HEIGHT        200

/*****************************************************************************!
 * Exported Class : SignalTabWindow
 *****************************************************************************/
class SignalTabWindow : public QTabWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SignalTabWindow               ();

 //! Destructor
 public :
  ~SignalTabWindow              ();

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

#endif /* _signaltabwindow_h_*/
