/*****************************************************************************
 * FILE NAME    : EquipmentInformation.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _equipmentinformation_h_
#define _equipmentinformation_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalsInformation.h"
#include "NCUEquipment.h"
#include "sqlite3.h"
#include "EquipmentSignalPair.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : EquipmentInformation
 *****************************************************************************/
class EquipmentInformation : public SignalsInformation
{
  Q_OBJECT;

 //! Constructors
 public :
  EquipmentInformation          ();

 //! Destructor
 public :
  ~EquipmentInformation         ();

 //! Public Methods
 public :
  void                          AddEquipment            (NCUEquipment* InEquipment);
  NCUEquipment*                 FindEquipmentByID       (int InTrack, int InID);
  void                          SQLRead                 (sqlite3* InDatabase);
  int                           GetCountByTrack         (int InTrack);

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
  QList<NCUEquipment*>          equipment;;
  QList<EquipmentSignalPair*>   equipmentPairs;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _equipmentinformation_h_*/
