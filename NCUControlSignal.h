/*****************************************************************************
 * FILE NAME    : NCUControlSignal.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncucontrolsignal_h_
#define _ncucontrolsignal_h_

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
 * Exported Class : NCUControlSignal
 *****************************************************************************/
class NCUControlSignal : public NCUSignal
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUControlSignal              ();

 //! Destructor
 public :
  ~NCUControlSignal             ();

 //! Public Methods
 public :
  bool                          Equal                   (NCUControlSignal* InAlarm);

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

#endif /* _ncucontrolsignal_h_*/
