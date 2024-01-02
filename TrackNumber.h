/*****************************************************************************
 * FILE NAME    : TrackNumber.h
 * DATE         : January 02 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _tracknumber_h_
#define _tracknumber_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TrackNumber
 *****************************************************************************/
class TrackNumber : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TrackNumber                   (int InNumber);

 //! Destructor
 public :
  ~TrackNumber                  ();

 //! Public Methods
 public :
  int                           GetNumber               (void);
  void                          SetNumber               (int InNumber);
  QString                       ToString                (void);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  int                           Number;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _tracknumber_h_*/
