/*****************************************************************************
 * FILE NAME    : SampleDisplayWindow.cpp
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
#include "SampleDisplayWindow.h"
#include "SampleInformation.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : SampleDisplayWindow
 *****************************************************************************/
SampleDisplayWindow::SampleDisplayWindow
(QString InText) : SignalDisplayWindow(InText)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SampleDisplayWindow
 *****************************************************************************/
SampleDisplayWindow::~SampleDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SampleDisplayWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  SetSampleInformation();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SampleDisplayWindow::CreateSubWindows()
{
  sampleDisplayFormWindow = new SampleDisplayForm();  
  sampleDisplayFormWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SampleDisplayWindow::InitializeSubWindows()
{
  sampleDisplayFormWindow = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SampleDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   sampleDisplayFormWindowW;
  int                                   sampleDisplayFormWindowH;
  int                                   sampleDisplayFormWindowY;
  int                                   sampleDisplayFormWindowX;
  QSize					size;  
  int					width;
  int					height;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  if ( statsWindow ) {
    statsWindow->resize(width, SIGNAL_STATS_WINDOW_HEIGHT);
  }

  sampleDisplayFormWindowX = 0;  
  sampleDisplayFormWindowY = SIGNAL_STATS_WINDOW_HEIGHT;
  sampleDisplayFormWindowW = width;
  sampleDisplayFormWindowH = height - SIGNAL_STATS_WINDOW_HEIGHT;
  sampleDisplayFormWindow->move(sampleDisplayFormWindowX, sampleDisplayFormWindowY);
  sampleDisplayFormWindow->resize(sampleDisplayFormWindowW, sampleDisplayFormWindowH);
}

/*****************************************************************************!
 * Function : SetSampleInformation
 *****************************************************************************/
void
SampleDisplayWindow::SetSampleInformation(void)
{
  int                                   combinedSignals;
  int                                   trackDiffer;
  int                                   track2Missing;
  int                                   track3Missing;
  int                                   track3Count;
  int                                   track2Count;
  SampleInformation*                    sampleInfo;
  
  sampleInfo = MainConfig::sampleInformation;

  track2Count = sampleInfo->GetTrack2Count();
  track3Count = sampleInfo->GetTrack3Count();

  track2Missing = sampleInfo->GetTrack2MissingCount();
  track3Missing = sampleInfo->GetTrack3MissingCount();

  trackDiffer = sampleInfo->GetTrackDifferCount();
  combinedSignals = sampleInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(track2Count, track3Count);
  statsWindow->SetMissingTrackCounts(track2Missing, track3Missing);
  statsWindow->SetTrackDifferCount(trackDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);  
}
