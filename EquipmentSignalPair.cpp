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
(int InID, NCUEquipment* InTrackASignal, NCUEquipment* InTrackBSignal) : QWidget()
{
  id = InID;
  TrackASignal = InTrackASignal;
  TrackBSignal = InTrackBSignal;
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
 * Function : AddTrackBSignal
 *****************************************************************************/
void
EquipmentSignalPair::AddTrackBSignal
(NCUEquipment* InTrackB)
{
  TrackBSignal = InTrackB;
}

/*****************************************************************************!
 * Function : GetTrackA
 *****************************************************************************/
NCUEquipment*
EquipmentSignalPair::GetTrackA(void)
{
  return TrackASignal;
}

/*****************************************************************************!
 * Function : GetTrackB
 *****************************************************************************/
NCUEquipment*
EquipmentSignalPair::GetTrackB(void)
{
  return TrackBSignal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
EquipmentSignalPair::Differ(void)
{
  if ( NULL == TrackASignal || NULL == TrackBSignal ) {
    return false;
  }
  return ! TrackASignal->Equal(TrackBSignal);
}
