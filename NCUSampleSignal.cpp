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
 * Static Data
 *****************************************************************************/
QStringList
NCUSampleSignal::Tags = QStringList()
  << "SAMPLEName"
  << "Unit"
  << "SIndx"
  << "SChan"
  << "ValType"
  << "StorThreshold"
  << "StorInt"
  << "EvalExpRPN"
  << "EvalExpFull"
  << "Range"
  << "DisplayAttr"
  << "DisplayLvl"
  << "DisplayID"
  << "DispFmt"
  << "DispExpRPN"
  << "DispExpFull"
  << "Enums";
  
/*****************************************************************************!
 * Function : NCUSampleSignal
 *****************************************************************************/
NCUSampleSignal::NCUSampleSignal
() : NCUSignal()
{
  for ( auto tag : Tags ) {
    Values[tag] = QString();
  }
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
NCUSampleSignal::Equal
(NCUSampleSignal* InSample)
{
  for ( auto tag : Tags ) {
    if ( Values[tag] != InSample->GetValue(tag) ) {
      return false;
    }
  }
  
  return true;
}
