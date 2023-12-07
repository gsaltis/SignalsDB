/*****************************************************************************
 * FILE NAME    : NCUSettingSignal.cpp
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
#include "NCUSettingSignal.h"

/*****************************************************************************!
 * Function : NCUSettingSignal
 *****************************************************************************/
NCUSettingSignal::NCUSettingSignal
() : NCUSignal()
{
  IDName = "SID";
}

/*****************************************************************************!
 * Function : ~NCUSettingSignal
 *****************************************************************************/
NCUSettingSignal::~NCUSettingSignal
()
{
}

/*****************************************************************************!
 * Function : Equal
 *****************************************************************************/
bool
NCUSettingSignal::Equal
(NCUSettingSignal* InSetting)
{
  if ( Unit != InSetting->Unit ) {
    return false;
  }
  
  if ( SIndx != InSetting->SIndx ) {
    return false;
  }
  
  if ( SChan != InSetting->SChan ) {
    return false;
  }
  
  if ( ValType != InSetting->ValType ) {
    return false;
  }
  
  if ( Def != InSetting->Def ) {
    return false;
  }
  
  if ( Range != InSetting->Range ) {
    return false;
  }
  
  if ( DisplayAttr != InSetting->DisplayAttr ) {
    return false;
  }
  
  if ( SetAttr != InSetting->SetAttr ) {
    return false;
  }
  
  if ( SetExpRPN != InSetting->SetExpRPN ) {
    return false;
  }
  
  if ( SetExpFull != InSetting->SetExpFull ) {
    return false;
  }
  
  if ( Auth != InSetting->Auth ) {
    return false;
  }
  
  if ( DisplayID != InSetting->DisplayID ) {
    return false;
  }
  
  if ( DispFmt != InSetting->DispFmt ) {
    return false;
  }
  
  if ( ChID != InSetting->ChID ) {
    return false;
  }
  
  if ( Step != InSetting->Step ) {
    return false;
  }
  
  if ( CExpRPN != InSetting->CExpRPN ) {
    return false;
  }
  
  if ( CExpFull != InSetting->CExpFull ) {
    return false;
  }
  
  if ( Persist != InSetting->Persist ) {
    return false;
  }
  
  if ( DispExpRPN != InSetting->DispExpRPN ) {
    return false;
  }
  
  if ( DispExpFull != InSetting->DispExpFull ) {
    return false;
  }
  
  if ( States != InSetting->States ) {
    return false;
  }
  
  if ( OnCtrl != InSetting->OnCtrl ) {
    return false;
  }
  
  return true;
}
