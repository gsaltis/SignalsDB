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
(int InID, int InSID, NCUSettingSignal* InTrack2Signal, NCUSettingSignal* InTrack3Signal) : QWidget()
{
  id = InID;
  sid = InSID;
  Track2Signal = InTrack2Signal;
  Track3Signal = InTrack3Signal;
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
 * Function : AddTrack3Signal
 *****************************************************************************/
void
SettingSignalPair::AddTrack3Signal
(NCUSettingSignal* InTrack3)
{
  Track3Signal = InTrack3;
}

/*****************************************************************************!
 * Function : GetTrack2
 *****************************************************************************/
NCUSettingSignal*
SettingSignalPair::GetTrack2()
{
  return Track2Signal;
}

/*****************************************************************************!
 * Function : GetTrack3
 *****************************************************************************/
NCUSettingSignal*
SettingSignalPair::GetTrack3()
{
  return Track3Signal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
SettingSignalPair::Differ()
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
SettingSignalPair::Differ
(QString InTag)
{
  if ( NULL == Track2Signal || NULL == Track3Signal ) {
    return false;
  }
  return Track2Signal->GetValue(InTag) != Track3Signal->GetValue(InTag);
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

  if ( NULL == Track2Signal || NULL == Track3Signal ) {
    return;
  }

  for ( auto format : InFormats ) {
    tag = format->GetElementKey();
    if ( Track2Signal->GetValue(tag) == Track3Signal->GetValue(tag) ) {
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

