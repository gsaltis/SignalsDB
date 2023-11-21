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
  bool                                  operator==(NCUSampleSignal* InSample);
  
 //! Public Data
 public :
  QString                               Unit;
  QString                               SIndx;
  QString                               SChan;
  QString                               ValType;
  QString                               StorThreshold;
  QString                               StorInt;
  QString                               EvalExpRPN;
  QString                               EvalExpFull;
  QString                               Range;
  QString                               DisplayAttr;
  QString                               DisplayLvl;
  QString                               DisplayID;
  QString                               DispFmt;
  QString                               DispExpRPN;
  QString                               DispExpFull;
  QString                               Enums;

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
