/*****************************************************************************
 * FILE NAME    : NCUEquipment.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncuequipment_h_
#define _ncuequipment_h_

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
 * Exported Class : NCUEquipment
 *****************************************************************************/
class NCUEquipment : public NCUSignal
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUEquipment                  ();

 //! Destructor
 public :
  ~NCUEquipment                 ();

 //! Public Methods
 public :
  bool                                  Equal                   (NCUEquipment* InEquipment);
  void                                  Dump                    (void);

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

#endif /* _ncuequipment_h_*/
