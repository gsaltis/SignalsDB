/*****************************************************************************
 * FILE NAME    : NCUAlarmSignal.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncualarmsignal_h_
#define _ncualarmsignal_h_

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
 * Exported Class : NCUAlarmSignal
 *****************************************************************************/
class NCUAlarmSignal : public NCUSignal
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUAlarmSignal                ();

 //! Destructor
 public :
  ~NCUAlarmSignal               ();

 //! Public Methods
 public :
  bool                                  operator==(NCUAlarmSignal* InAlarm);
 //! Public Data
 public :
  QString                               Level;
  QString                               ExpRPN;
  QString                               EXPFull;
  QString                               Delay;
  QString                               SuppressRPN;
  QString                               SuppressFull;
  QString                               Relay;
  QString                               Help;

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

#endif /* _ncualarmsignal_h_*/
