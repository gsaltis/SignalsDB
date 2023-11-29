/*****************************************************************************
 * FILE NAME    : EquipmentSignalPair.cpp
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
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

/*****************************************************************************!
 * Function : AddTrack3Signal
 *****************************************************************************/
void
EquipmentSignalPair::AddTrack3Signal
(NCUEquipment* InTrack3)
{
  Track3Signal = InTrack3;
}

/*****************************************************************************!
 * Function : GetTrack2
 *****************************************************************************/
NCUEquipment*
EquipmentSignalPair::GetTrack2(void)
{
  return Track2Signal;
}

/*****************************************************************************!
 * Function : GetTrack3
 *****************************************************************************/
NCUEquipment*
EquipmentSignalPair::GetTrack3(void)
{
  return Track3Signal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
EquipmentSignalPair::Differ(void)
{
  if ( NULL == Track2Signal || NULL == Track3Signal ) {
    return false;
  }
  return ! Track2Signal->Equal(Track3Signal);
}
