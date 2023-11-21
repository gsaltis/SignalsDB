/*****************************************************************************
 * FILE NAME    : NCUSampleSignal.cpp
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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUSampleSignal.h"

/*****************************************************************************!
 * Function : NCUSampleSignal
 *****************************************************************************/
NCUSampleSignal::NCUSampleSignal
() : NCUSignal()
{
  IDName = "SID";
}

/*****************************************************************************!
 * Function : ~NCUSampleSignal
 *****************************************************************************/
NCUSampleSignal::~NCUSampleSignal
()
{
}


/*****************************************************************************!
 * Function : opeator==
 *****************************************************************************/
bool
NCUSampleSignal::operator==
(NCUSampleSignal* InSample)
{
  if ( Unit != InSample->Unit ) {
    return false;
  }
  
  if ( SIndx != InSample->SIndx ) {
    return false;
  }
  
  if ( SChan != InSample->SChan ) {
    return false;
  }
  
  if ( ValType != InSample->ValType ) {
    return false;
  }
  
  if ( StorThreshold != InSample->StorThreshold ) {
    return false;
  }
  
  if ( StorInt != InSample->StorInt ) {
    return false;
  }
  
  if ( EvalExpRPN != InSample->EvalExpRPN ) {
    return false;
  }
  
  if ( EvalExpFull != InSample->EvalExpFull ) {
    return false;
  }
  
  if ( Range != InSample->Range ) {
    return false;
  }
  
  if ( DisplayAttr != InSample->DisplayAttr ) {
    return false;
  }
  
  if ( DisplayLvl != InSample->DisplayLvl ) {
    return false;
  }
  
  if ( DisplayID != InSample->DisplayID ) {
    return false;
  }
  
  if ( DispFmt != InSample->DispFmt ) {
    return false;
  }
  
  if ( DispExpRPN != InSample->DispExpRPN ) {
    return false;
  }
  
  if ( DispExpFull != InSample->DispExpFull ) {
    return false;
  }
  
  if ( Enums != InSample->Enums ) {
    return false;
  }
  
  return true;
}
