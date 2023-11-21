/*****************************************************************************
 * FILE NAME    : NCUEquipmentSet.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncuequipmentset_h_
#define _ncuequipmentset_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUEquipment.h"
#include "sqlite3.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : NCUEquipmentSet
 *****************************************************************************/
class NCUEquipmentSet : public QWidget, QList<NCUEquipment*>
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUEquipmentSet               ();

 //! Destructor
 public :
  ~NCUEquipmentSet              ();

 //! Public Methods
 public :
  void                          SQLRead                 (sqlite3* InDatabase);

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

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _ncuequipmentset_h_*/
