/*****************************************************************************
 * FILE NAME    : NCUAlarmSignal.cpp
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
#include "NCUAlarmSignal.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
QStringList NCUAlarmSignal::Tags = 
  QStringList() << "AlarmName"
  << "Level"
  << "ExpRPN"
  << "ExpFulll"
  << "SuppressRPN"
  << "SuppressFull"
  << "Relay"
  << "Help";

/*****************************************************************************!
 * Function : NCUAlarmSignal
 *****************************************************************************/
NCUAlarmSignal::NCUAlarmSignal
() : NCUSignal()
{
  for ( auto tag : Tags ) {
    Values[tag] = QString();
  }
}

/*****************************************************************************!
 * Function : ~NCUAlarmSignal
 *****************************************************************************/
NCUAlarmSignal::~NCUAlarmSignal
()
{
}

/*****************************************************************************!
 * Function : Equal
 *****************************************************************************/
bool
NCUAlarmSignal::Equal
(NCUAlarmSignal* InAlarm)
{
  for ( auto tag : Tags ) {
    if ( Values[tag] != InAlarm->GetValue(tag) ) {
      return false;
    }
  }
  return true;
}

