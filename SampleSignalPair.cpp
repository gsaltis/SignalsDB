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
(int InID, int InSID, NCUSampleSignal* InTrack2Signal, NCUSampleSignal* InTrack3Signal) : QWidget()
{
  id = InID;
  sid = InSID;
  Track2Signal = InTrack2Signal;
  Track3Signal = InTrack3Signal;
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
 * Function : AddTrack3Signal
 *****************************************************************************/
void
SampleSignalPair::AddTrack3Signal
(NCUSampleSignal* InTrack3)
{
  Track3Signal = InTrack3;
}

/*****************************************************************************!
 * Function : GetTrack2
 *****************************************************************************/
NCUSampleSignal*
SampleSignalPair::GetTrack2()
{
  return Track2Signal;
}

/*****************************************************************************!
 * Function : GetTrack3
 *****************************************************************************/
NCUSampleSignal*
SampleSignalPair::GetTrack3()
{
  return Track3Signal;
}

/*****************************************************************************!
 * Function : Differ
 *****************************************************************************/
bool
SampleSignalPair::Differ()
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
SampleSignalPair::Differ
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
SampleSignalPair::GetDifferCounts
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
  if ( Track2Signal ) {
    Track2Signal->AddXCLRow(InWorksheet, row, 3);
    row++;
  }
  if ( Track3Signal ) {
    Track3Signal->AddXCLRow(InWorksheet, row, 3);
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
  if ( Track2Signal == NULL || Track3Signal == NULL ) {
    return row;
  }
  Track2Signal->AddXCLRow(InWorksheet, row, 3);
  row++;

  Track3Signal->AddXCLRow(InWorksheet, row, 3, true);
  row++;
  return row;
}
