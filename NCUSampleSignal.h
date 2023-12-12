/*****************************************************************************
 * FILE NAME    : NCUSampleSignal.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncusamplesignal_h_
#define _ncusamplesignal_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUSignal.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : NCUSampleSignal
 *****************************************************************************/
class NCUSampleSignal : public NCUSignal
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUSampleSignal               ();

 //! Destructor
 public :
  ~NCUSampleSignal              ();

 //! Public Methods
 public :
  bool                                  Equal   (NCUSampleSignal* InSample);
  
 //! Public Data
 public :
  static QStringList            Tags;

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _ncusamplesignal_h_*/
