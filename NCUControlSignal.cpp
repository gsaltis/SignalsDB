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
 * Static Data
 *****************************************************************************/
QStringList
NCUControlSignal::Tags = QStringList()
  << "CTRLName"
  << "Unit"
  << "SIndx"
  << "SChan"
  << "ValType"
  << "Defaults"
  << "Range"
  << "DisplayAttr"
  << "CtrlAttr"
  << "Threshold"
  << "CableExpRPN"
  << "CableExpFull"
  << "Auth"
  << "DisplayID"
  << "DispFmt"
  << "ChID"
  << "CStep"
  << "CParam"
  << "CexpRPN"
  << "CexpFullDispExp"
  << "States"
  << "CAction";
  
/*****************************************************************************!
 * Function : NCUControlSignal
 *****************************************************************************/
NCUControlSignal::NCUControlSignal
() : NCUSignal()
{
  for ( auto tag : Tags ) {
    Values[tag] = QString();
  }
}

/*****************************************************************************!
 * Function : ~NCUControlSignal
 *****************************************************************************/
NCUControlSignal::~NCUControlSignal
()
{
}

/*****************************************************************************!
 * Function : Equal
 *****************************************************************************/
bool
NCUControlSignal::Equal
(NCUControlSignal* InControlSignal)
{
  for ( auto tag : Tags ) {
    if ( Values[tag] != InControlSignal->GetValue(tag) ) {
      return false;
    }
  }
  return true;
}
