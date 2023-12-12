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

#endif /* _ncusettingsignal_h_*/
