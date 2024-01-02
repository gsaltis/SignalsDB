/*****************************************************************************
 * FILE NAME    : AlarmSignalPair.cpp
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "AlarmSignalPair.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : AlarmSignalPair
 *****************************************************************************/
AlarmSignalPair::AlarmSignalPair
(int InID, int InSID, NCUAlarmSignal* InTrackASignal, NCUAlarmSignal* InTrackBSignal) : QWidget()
{
  id = InID;
  sid = InSID;
  TrackASignal = InTrackASignal;
  TrackBSignal = InTrackBSignal;
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
 * Function : AddTrackBSignal
 *****************************************************************************/
void
AlarmSignalPair::AddTrackBSignal
(NCUAlarmSignal* InTrackB)
{
  TrackBSignal = InTrackB;
}

/*****************************************************************************!
 * Function : GetTrackA
 *****************************************************************************/
NCUAlarmSignal*
AlarmSignalPair::GetTrackA()
{
  return TrackASignal;
}

/*****************************************************************************!
 * Function : GetTrackB
 *****************************************************************************/
NCUAlarmSignal*
AlarmSignalPair::GetTrackB()
{
  return TrackBSignal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
AlarmSignalPair::Differ()
{
  if ( NULL == TrackASignal || NULL == TrackBSignal ) {
    return false;
  }
  return ! TrackASignal->Equal(TrackBSignal);
}

/*****************************************************************************!
 * Function : GetDifferCounts
 *****************************************************************************/
void
AlarmSignalPair::GetDifferCounts
(int &InMajor, int &InMinor, QList<ElementDisplayLineFormat*> InFormats)
{
  QString                               differsev;
  QString                               tag;
  
  InMinor = 0;
  InMajor = 0;

  if ( NULL == TrackASignal || NULL == TrackBSignal ) {
    return;
  }

  for ( auto format : InFormats ) {
    tag = format->GetElementKey();
    if ( TrackASignal->GetValue(tag) == TrackBSignal->GetValue(tag) ) {
      continue;
    }
    differsev = format->GetDifferenceSeverity();
    if ( format->GetDifferenceSeverity() == "Major" ) {
      InMajor++;
      continue;
    }
    if ( format->GetDifferenceSeverity() == "Minor" ) {
      InMinor++;
    }
  }
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
AlarmSignalPair::Differ
(QString InTag)
{
  if ( NULL == TrackASignal || NULL == TrackBSignal ) {
    return false;
  }
  return TrackASignal->GetValue(InTag) != TrackBSignal->GetValue(InTag);
}
