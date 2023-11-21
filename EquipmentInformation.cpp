/*****************************************************************************
 * FILE NAME    : EquipmentInformation.cpp
 * DATE         : November 21 2023
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
#include "EquipmentInformation.h"

/*****************************************************************************!
 * Function : EquipmentInformation
 *****************************************************************************/
EquipmentInformation::EquipmentInformation
() : SignalsInformation()
{
}

/*****************************************************************************!
 * Function : ~EquipmentInformation
 *****************************************************************************/
EquipmentInformation::~EquipmentInformation
()
{
}

/*****************************************************************************!
 * Function : AddEquipment
 *****************************************************************************/
void
EquipmentInformation::AddEquipment
(NCUEquipment* InEquipment)
{
  if ( NULL == InEquipment ) {
    return;
  }
  equipment << InEquipment;
}

/*****************************************************************************!
 * Function : FindEquipmentByID
 *****************************************************************************/
NCUEquipment*
EquipmentInformation::FindEquipmentByID
(int InTrack, int InID)
{
  for ( auto i : equipment ) {
    if ( i->GetTrack() == InTrack && i->GetID() == InID ) {
      return i;
    }
  }
  return NULL;
}
