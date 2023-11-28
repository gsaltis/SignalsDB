/*****************************************************************************
 * FILE NAME    : EquipmentSignalPair.cpp
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "EquipmentSignalPair.h"

/*****************************************************************************!
 * Function : EquipmentSignalPair
 *****************************************************************************/
EquipmentSignalPair::EquipmentSignalPair
(int InID, NCUEquipment* InTrack2Signal, NCUEquipment* InTrack3Signal) : QWidget()
{
  id = InID;
  Track2Signal = InTrack2Signal;
  Track3Signal = InTrack3Signal;
}

/*****************************************************************************!
 * Function : ~EquipmentSignalPair
 *****************************************************************************/
EquipmentSignalPair::~EquipmentSignalPair
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
EquipmentSignalPair::GetID(void)
{
  return id;
}
