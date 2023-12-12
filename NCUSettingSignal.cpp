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
 * Static Data
 *****************************************************************************/
QStringList
NCUSettingSignal::Tags = QStringList()
  << "SETName"
  << "Unit"
  << "SIndx"
  << "SChan"
  << "ValType"
  << "Def"
  << "Range"
  << "DisplayAttr"
  << "SetAttr"
  << "SetExpRPN"
  << "SetExpFull"
  << "Auth"
  << "DisplayID"
  << "DispFmt"
  << "ChID"
  << "Step"
  << "CExpRPN"
  << "CExpFull"
  << "Persist"
  << "DispExpRPN"
  << "DispExpFull"
  << "States"
  << "OnCtrl";

/*****************************************************************************!
 * Function : NCUSettingSignal
 *****************************************************************************/
NCUSettingSignal::NCUSettingSignal
() : NCUSignal()
{
  for ( auto tag : Tags ) {
    Values[tag] = QString();
  }
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
  for ( auto tag : Tags ) {
    if ( Values[tag] != InSetting->GetValue(tag) ) {
      return false;
    }
  }
  return true;
}
