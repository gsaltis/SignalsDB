/*****************************************************************************
 * FILE NAME    : AlarmSignalPair.cpp
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "AlarmSignalPair.h"

/*****************************************************************************!
 * Function : AlarmSignalPair
 *****************************************************************************/
AlarmSignalPair::AlarmSignalPair
(int InID, int InSID, NCUAlarmSignal* InTrack2Signal, NCUAlarmSignal* InTrack3Signal) : QWidget()
{
  id = InID;
  sid = InSID;
  Track2Signal = InTrack2Signal;
  Track3Signal = InTrack3Signal;
}

/*****************************************************************************!
 * Function : ~AlarmSignalPair
 *****************************************************************************/
AlarmSignalPair::~AlarmSignalPair
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
AlarmSignalPair::GetID()
{
  return id;
}

/*****************************************************************************!
 * Function : GetSID
 *****************************************************************************/
int
AlarmSignalPair::GetSID()
{
  return sid;
}

/*****************************************************************************!
 * Function : AddTrack3Signal
 *****************************************************************************/
void
AlarmSignalPair::AddTrack3Signal
(NCUAlarmSignal* InTrack3)
{
  Track3Signal = InTrack3;
}

/*****************************************************************************!
 * Function : GetTrack2
 *****************************************************************************/
NCUAlarmSignal*
AlarmSignalPair::GetTrack2()
{
  return Track2Signal;
}

/*****************************************************************************!
 * Function : GetTrack3
 *****************************************************************************/
NCUAlarmSignal*
AlarmSignalPair::GetTrack3()
{
  return Track3Signal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
AlarmSignalPair::Differ()
{
  if ( NULL == Track2Signal || NULL == Track3Signal ) {
    return false;
  }
  return ! Track2Signal->Equal(Track3Signal);
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
AlarmSignalPair::Differ
(QString InTag)
{
  if ( NULL == Track2Signal || NULL == Track3Signal ) {
    return false;
  }
  return Track2Signal->GetValue(InTag) != Track3Signal->GetValue(InTag);
}
