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
#define ELEMENT_DISPLAY_LINE_HEIGHT     25

/*****************************************************************************!
 * Exported Class : ElementDisplayLine
 *****************************************************************************/
class ElementDisplayLine : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  ElementDisplayLine            (QString InLabelText, QColor InBackgroundColor, QColor InValueColor);

 //! Destructor
 public :
  ~ElementDisplayLine           ();

 //! Public Methods
 public :
  void                          SetTrack2Value          (QString InValue);
  void                          SetTrack3Value          (QString InValue);
  void                          Clear                   (void);
  void                          Compare                 (void);

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
  QLabel*                       SignalLabel;
  int                           SignalLabelWidth;
  QColor                        NormalColor;
  QColor                        DifferColor;
  QLabel*                       Track2Value;
  QLabel*                       Track3Value;
  QLabel*                       Spacer;
  QColor                        SpacerColor;
  int                           SpacerWidth;
  QColor                        ValueColor;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _elementdisplayline_h_*/
