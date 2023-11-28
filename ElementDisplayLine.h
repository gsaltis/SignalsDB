/*****************************************************************************
 * FILE NAME    : ElementDisplayLine.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _elementdisplayline_h_
#define _elementdisplayline_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define ELEMENT_DISPLAY_LINE_HEIGHT     30

/*****************************************************************************!
 * Exported Class : ElementDisplayLine
 *****************************************************************************/
class ElementDisplayLine : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  ElementDisplayLine            (QString InLabelText, QColor InBackgroundColor);

 //! Destructor
 public :
  ~ElementDisplayLine           ();

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
  QString                       labelText;
  QColor                        backgroundColor;
  QLabel*                       label;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _elementdisplayline_h_*/
