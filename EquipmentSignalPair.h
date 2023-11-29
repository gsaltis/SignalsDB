/*****************************************************************************
 * FILE NAME    : EquipmentSignalPair.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _equipmentsignalpair_h_
#define _equipmentsignalpair_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : EquipmentSignalPair
 *****************************************************************************/
class EquipmentSignalPair : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  EquipmentSignalPair           (int InID, NCUEquipment* InTrack2Signal, NCUEquipment* InTrack3Signal);

 //! Destructor
 public :
  ~EquipmentSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   (void);
  void                          AddTrack3Signal         (NCUEquipment* InTrack3);
  NCUEquipment*                 GetTrack2               (void);
  NCUEquipment*                 GetTrack3               (void);
  bool                          Differ                  (void);

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
  NCUEquipment*                 Track2Signal;
  NCUEquipment*                 Track3Signal;
  int                           id;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _equipmentsignalpair_h_*/
