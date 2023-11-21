/*****************************************************************************
 * FILE NAME    : NCUControlSignal.cpp
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
#include "NCUControlSignal.h"

/*****************************************************************************!
 * Function : NCUControlSignal
 *****************************************************************************/
NCUControlSignal::NCUControlSignal
() : NCUSignal()
{
  IDName = "SID";
}

/*****************************************************************************!
 * Function : ~NCUControlSignal
 *****************************************************************************/
NCUControlSignal::~NCUControlSignal
()
{
}

/*****************************************************************************!
 * Function : operator==
 *****************************************************************************/
bool
NCUControlSignal::operator==(NCUControlSignal* InControl)
{
  if ( CTRLName != InControl->CTRLName ) {
    return false;
  }
  
  if ( Unit != InControl->Unit ) {
    return false;
  }
  
  if ( SIndx != InControl->SIndx ) {
    return false;
  }
  
  if ( SChan != InControl->SChan ) {
    return false;
  }
  
  if ( ValType != InControl->ValType ) {
    return false;
  }
  
  if ( Defaults != InControl->Defaults ) {
    return false;
  }
  
  if ( Range != InControl->Range ) {
    return false;
  }
  
  if ( DisplayAttr != InControl->DisplayAttr ) {
    return false;
  }
  
  if ( CtrlAttr != InControl->CtrlAttr ) {
    return false;
  }
  
  if ( Threshold != InControl->Threshold ) {
    return false;
  }
  
  if ( CableExpRPN != InControl->CableExpRPN ) {
    return false;
  }
  
  if ( CableExpFull != InControl->CableExpFull ) {
    return false;
  }
  
  if ( Auth != InControl->Auth ) {
    return false;
  }
  
  if ( DisplayID != InControl->DisplayID ) {
    return false;
  }
  
  if ( DispFmt != InControl->DispFmt ) {
    return false;
  }
  
  if ( ChID != InControl->ChID ) {
    return false;
  }
  
  if ( CStep != InControl->CStep ) {
    return false;
  }
  
  if ( CParam != InControl->CParam ) {
    return false;
  }
  
  if ( CexpRPN != InControl->CexpRPN ) {
    return false;
  }
  
  if ( CexpFullDispExp != InControl->CexpFullDispExp ) {
    return false;
  }
  
  if ( States != InControl->States ) {
    return false;
  }
  
  if ( CAction != InControl->CAction ) {
    return false;
  }
  
  return true;
}

