/*****************************************************************************
 * FILE NAME    : SignalDisplayForm.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _signaldisplayform_h_
#define _signaldisplayform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "ElementDisplayLine.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SIGNAL_DISPLAY_FORM_X           200
#define SIGNAL_DISPLAY_FORM_Y           200
#define SIGNAL_DISPLAY_FORM_WIDTH       200
#define SIGNAL_DISPLAY_FORM_HEIGHT      200

/*****************************************************************************!
 * Exported Class : SignalDisplayForm
 *****************************************************************************/
class SignalDisplayForm : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SignalDisplayForm             ();

 //! Destructor
 public :
  ~SignalDisplayForm            ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  QList<ElementDisplayLine*>    elementLines;
  
 //! Protected Data
 protected :
  QColor                        ValueColors[2];
  
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

#endif /* _signaldisplayform_h_*/
