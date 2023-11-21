/*****************************************************************************
 * FILE NAME    : WindowHeader.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _windowheader_h_
#define _windowheader_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QString>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define WINDOW_HEADER_HEIGHT            40

/*****************************************************************************!
 * Exported Class : WindowHeader
 *****************************************************************************/
class WindowHeader : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  WindowHeader                  (QString InText, QWidget* InParent);

 //! Destructor
 public :
  ~WindowHeader                 ();

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
  QLabel*                       TextLabel;
  QString                       text;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _windowheader_h_*/
