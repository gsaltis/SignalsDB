/*****************************************************************************
 * FILE NAME    : ControlSignalPair.cpp
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
#include "ControlSignalPair.h"

/*****************************************************************************!
 * Function : ControlSignalPair
 *****************************************************************************/
ControlSignalPair::ControlSignalPair
(int InID, int InSID, NCUControlSignal* InTrack2Signal, NCUControlSignal* InTrack3Signal) : QWidget()
{
  id = InID;
  sid = InSID;
  Track2Signal = InTrack2Signal;
  Track3Signal = InTrack3Signal;
}

/*****************************************************************************!
 * Function : ~ControlSignalPair
 *****************************************************************************/
ControlSignalPair::~ControlSignalPair
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
ControlSignalPair::GetID()
{
  return id;
}

/*****************************************************************************!
 * Function : GetSID
 *****************************************************************************/
int
ControlSignalPair::GetSID()
{
  return sid;
}

/*****************************************************************************!
 * Function : AddTrack3Signal
 *****************************************************************************/
void
ControlSignalPair::AddTrack3Signal
(NCUControlSignal* InTrack3)
{
  Track3Signal = InTrack3;
}

/*****************************************************************************!
 * Function : GetTrack2
 *****************************************************************************/
NCUControlSignal*
ControlSignalPair::GetTrack2()
{
  return Track2Signal;
}

/*****************************************************************************!
 * Function : GetTrack3
 *****************************************************************************/
NCUControlSignal*
ControlSignalPair::GetTrack3()
{
  return Track3Signal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
ControlSignalPair::Differ()
{
  if ( NULL == Track2Signal || NULL == Track3Signal ) {
    return false;
  }
  return ! Track2Signal->Equal(Track3Signal);
}
