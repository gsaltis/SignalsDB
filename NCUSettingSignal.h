/*****************************************************************************
 * FILE NAME    : NCUSettingSignal.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncusettingsignal_h_
#define _ncusettingsignal_h_

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
 * Exported Class : NCUSettingSignal
 *****************************************************************************/
class NCUSettingSignal : public NCUSignal
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUSettingSignal              ();

 //! Destructor
 public :
  ~NCUSettingSignal             ();

 //! Public Methods
 public :
  bool                                  Equal                   (NCUSettingSignal* InSetting);
  
 //! Public Data
 public :
  QString                               SETName;
  QString                               Unit;
  QString                               SIndx;
  QString                               SChan;
  QString                               ValType;
  QString                               Def;
  QString                               Range;
  QString                               DisplayAttr;
  QString                               SetAttr;
  QString                               SetExpRPN;
  QString                               SetExpFull;
  QString                               Auth;
  QString                               DisplayID;
  QString                               DispFmt;
  QString                               ChID;
  QString                               Step;
  QString                               CExpRPN;
  QString                               CExpFull;
  QString                               Persist;
  QString                               DispExpRPN;
  QString                               DispExpFull;
  QString                               States;
  QString                               OnCtrl;

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

#endif /* _ncusettingsignal_h_*/
