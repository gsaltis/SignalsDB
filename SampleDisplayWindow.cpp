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
  int                                   totalMinorDiffer;
  int                                   totalMajorDiffer;
  int                                   trackMinorDiffer;
  int                                   trackMajorDiffer;
  int                                   combinedSignals;
  int                                   trackAMissing;
  int                                   trackBMissing;
  int                                   trackBCount;
  int                                   trackACount;
  SampleInformation*                    sampleInfo;
  
  sampleInfo = MainConfig::sampleInformation;

  trackACount = sampleInfo->GetTrackACount();
  trackBCount = sampleInfo->GetTrackBCount();

  trackAMissing = sampleInfo->GetTrackAMissingCount();
  trackBMissing = sampleInfo->GetTrackBMissingCount();

  sampleInfo->GetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                  totalMinorDiffer, trackMinorDiffer);
  
  combinedSignals = sampleInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(trackACount, trackBCount);
  statsWindow->SetMissingTrackCounts(trackAMissing, trackBMissing);
  statsWindow->SetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                   totalMinorDiffer, trackMinorDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);  
}
