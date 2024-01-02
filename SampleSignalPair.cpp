/*****************************************************************************
 * FILE NAME    : SampleSignalPair.cpp
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
#include "SampleSignalPair.h"

/*****************************************************************************!
 * Function : SampleSignalPair
 *****************************************************************************/
SampleSignalPair::SampleSignalPair
(int InID, int InSID, NCUSampleSignal* InTrackASignal, NCUSampleSignal* InTrackBSignal) : QWidget()
{
  id = InID;
  sid = InSID;
  TrackASignal = InTrackASignal;
  TrackBSignal = InTrackBSignal;
}

/*****************************************************************************!
 * Function : ~SampleSignalPair
 *****************************************************************************/
SampleSignalPair::~SampleSignalPair
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
SampleSignalPair::GetID()
{
  return id;
}

/*****************************************************************************!
 * Function : GetSID
 *****************************************************************************/
int
SampleSignalPair::GetSID()
{
  return sid;
}

/*****************************************************************************!
 * Function : AddTrackBSignal
 *****************************************************************************/
void
SampleSignalPair::AddTrackBSignal
(NCUSampleSignal* InTrackB)
{
  TrackBSignal = InTrackB;
}

/*****************************************************************************!
 * Function : GetTrackA
 *****************************************************************************/
NCUSampleSignal*
SampleSignalPair::GetTrackA()
{
  return TrackASignal;
}

/*****************************************************************************!
 * Function : GetTrackB
 *****************************************************************************/
NCUSampleSignal*
SampleSignalPair::GetTrackB()
{
  return TrackBSignal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
SampleSignalPair::Differ()
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
SampleSignalPair::Differ
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
SampleSignalPair::GetDifferCounts
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
 * Function : AddXCLFullRows
 *****************************************************************************/
int
SampleSignalPair::AddXCLFullRows
(xlnt::worksheet* InWorksheet, int InStartingRow)
{
  int                                   row;
  InWorksheet->cell(1, InStartingRow).value(GetID());
  InWorksheet->cell(2, InStartingRow).value(GetSID());
  row = InStartingRow;
  if ( TrackASignal ) {
    TrackASignal->AddXCLRow(InWorksheet, row, 3);
    row++;
  }
  if ( TrackBSignal ) {
    TrackBSignal->AddXCLRow(InWorksheet, row, 3);
    row++;
  }
  return row;
}

/*****************************************************************************!
 * Function : AddXCLMajorDifferRows
 *****************************************************************************/
int
SampleSignalPair::AddXCLMajorDifferRows
(xlnt::worksheet* InWorksheet, int InStartingRow)
{
  int                                   row;
  InWorksheet->cell(1, InStartingRow).value(GetID());
  InWorksheet->cell(2, InStartingRow).value(GetSID());
  row = InStartingRow;
  if ( ! Differ() ) {
    return row;
  }
  if ( TrackASignal == NULL || TrackBSignal == NULL ) {
    return row;
  }
  TrackASignal->AddXCLRow(InWorksheet, row, 3);
  row++;

  TrackBSignal->AddXCLRow(InWorksheet, row, 3, true);
  row++;
  return row;
}
