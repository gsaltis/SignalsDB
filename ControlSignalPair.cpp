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
(int InID, int InSID, NCUControlSignal* InTrackASignal, NCUControlSignal* InTrackBSignal) : QWidget()
{
  id = InID;
  sid = InSID;
  TrackASignal = InTrackASignal;
  TrackBSignal = InTrackBSignal;
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
 * Function : AddTrackBSignal
 *****************************************************************************/
void
ControlSignalPair::AddTrackBSignal
(NCUControlSignal* InTrackB)
{
  TrackBSignal = InTrackB;
}

/*****************************************************************************!
 * Function : GetTrackA
 *****************************************************************************/
NCUControlSignal*
ControlSignalPair::GetTrackA()
{
  return TrackASignal;
}

/*****************************************************************************!
 * Function : GetTrackB
 *****************************************************************************/
NCUControlSignal*
ControlSignalPair::GetTrackB()
{
  return TrackBSignal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
ControlSignalPair::Differ()
{
  if ( NULL == TrackASignal || NULL == TrackBSignal ) {
    return false;
  }
  return ! TrackASignal->Equal(TrackBSignal);
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
ControlSignalPair::Differ
(QString InTag)
{
  if ( NULL == TrackASignal || NULL == TrackBSignal ) {
    return false;
  }
  return TrackASignal->GetValue(InTag) != TrackBSignal->GetValue(InTag);
}

/*****************************************************************************!
 * Function : GetDifferCounts
 *****************************************************************************/
void
ControlSignalPair::GetDifferCounts
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

