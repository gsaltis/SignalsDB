/*****************************************************************************
 * FILE NAME    : SettingSignalPair.cpp
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
#include "SettingSignalPair.h"

/*****************************************************************************!
 * Function : SettingSignalPair
 *****************************************************************************/
SettingSignalPair::SettingSignalPair
(int InID, int InSID, NCUSettingSignal* InTrackASignal, NCUSettingSignal* InTrackBSignal) : QWidget()
{
  id = InID;
  sid = InSID;
  TrackASignal = InTrackASignal;
  TrackBSignal = InTrackBSignal;
}

/*****************************************************************************!
 * Function : ~SettingSignalPair
 *****************************************************************************/
SettingSignalPair::~SettingSignalPair
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
SettingSignalPair::GetID()
{
  return id;
}

/*****************************************************************************!
 * Function : GetSID
 *****************************************************************************/
int
SettingSignalPair::GetSID()
{
  return sid;
}

/*****************************************************************************!
 * Function : AddTrackBSignal
 *****************************************************************************/
void
SettingSignalPair::AddTrackBSignal
(NCUSettingSignal* InTrackB)
{
  TrackBSignal = InTrackB;
}

/*****************************************************************************!
 * Function : GetTrackA
 *****************************************************************************/
NCUSettingSignal*
SettingSignalPair::GetTrackA()
{
  return TrackASignal;
}

/*****************************************************************************!
 * Function : GetTrackB
 *****************************************************************************/
NCUSettingSignal*
SettingSignalPair::GetTrackB()
{
  return TrackBSignal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
SettingSignalPair::Differ()
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
SettingSignalPair::Differ
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
SettingSignalPair::GetDifferCounts
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

