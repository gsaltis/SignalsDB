/*****************************************************************************
 * FILE NAME    : NCUEquipment.cpp
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUEquipment.h"

/*****************************************************************************!
 * Function : NCUEquipment
 *****************************************************************************/
NCUEquipment::NCUEquipment
() : NCUSignal()
{
  IDName = "Type";
}

/*****************************************************************************!
 * Function : ~NCUEquipment
 *****************************************************************************/
NCUEquipment::~NCUEquipment
()
{
}

/*****************************************************************************!
 * Function : operator==
 *****************************************************************************/
bool
NCUEquipment::operator==
(NCUEquipment* InEquipment)
{
  if ( TypeName != InEquipment->TypeName ) {
    return false;
  }
  
  if ( GroupName != InEquipment->GroupName ) {
    return false;
  }
  
  if ( NumofSamples != InEquipment->NumofSamples ) {
    return false;
  }
  
  if ( NumofCtrl != InEquipment->NumofCtrl ) {
    return false;
  }
  
  if ( NumofSet != InEquipment->NumofSet ) {
    return false;
  }
  
  if ( NumofAlarm != InEquipment->NumofAlarm ) {
    return false;
  }
  
  if ( Related != InEquipment->Related ) {
    return false;
  }

  return true;
}

