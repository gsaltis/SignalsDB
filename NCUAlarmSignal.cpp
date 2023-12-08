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
 * Function : NCUAlarmSignal
 *****************************************************************************/
NCUAlarmSignal::NCUAlarmSignal
() : NCUSignal()
{
  IDName = "SID";
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
  if ( AlarmName != InAlarm->AlarmName ) {
    return false;
  }
  
  if ( Level != InAlarm->Level ) {
    return false;
  }
  
  if ( ExpRPN != InAlarm->ExpRPN ) {
    return false;
  }
  
  if ( EXPFull != InAlarm->EXPFull ) {
    return false;
  }
  
  if ( Delay != InAlarm->Delay ) {
    return false;
  }
  
  if ( SuppressRPN != InAlarm->SuppressRPN ) {
    return false;
  }
  
  if ( SuppressFull != InAlarm->SuppressFull ) {
    return false;
  }
  
  if ( Relay != InAlarm->Relay ) {
    return false;
  }
  
  if ( Help != InAlarm->Help ) {
    return false;
  }
  
  return true;
}
