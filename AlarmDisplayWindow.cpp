/*****************************************************************************
 * FILE NAME    : AlarmDisplayWindow.cpp
 * DATE         : November 20 2023
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
#include "AlarmDisplayWindow.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : AlarmDisplayWindow
 *****************************************************************************/
AlarmDisplayWindow::AlarmDisplayWindow
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
 * Function : ~AlarmDisplayWindow
 *****************************************************************************/
AlarmDisplayWindow::~AlarmDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
AlarmDisplayWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  SetAlarmInformation();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
AlarmDisplayWindow::CreateSubWindows()
{
  alarmForm = new AlarmDisplayForm();  
  alarmForm->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
AlarmDisplayWindow::InitializeSubWindows()
{
  alarmForm = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
AlarmDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   alarmFormW;
  int                                   alarmFormH;
  int                                   alarmFormY;
  int                                   alarmFormX;
  QSize					size;  
  int					width;
  int					height;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  if ( statsWindow ) {
    statsWindow->resize(width, SIGNAL_STATS_WINDOW_HEIGHT);
  }

  alarmFormX = 0;
  alarmFormY = SIGNAL_STATS_WINDOW_HEIGHT;
  alarmFormW = width;
  alarmFormH = height - SIGNAL_STATS_WINDOW_HEIGHT;

  alarmForm->move(alarmFormX, alarmFormY);
  alarmForm->resize(alarmFormW, alarmFormH);
}

/*****************************************************************************!
 * Function : SetAlarmInformation
 *****************************************************************************/
void
AlarmDisplayWindow::SetAlarmInformation
()
{
  int                                   totalMinorDiffer;
  int                                   totalMajorDiffer;
  int                                   trackMinorDiffer;
  int                                   trackMajorDiffer;
  int                                   combinedSignals;
  int                                   trackAMissing;
  int                                   trackBMissing;
  int                                   trackACount;
  int                                   trackBCount;

  alarmInfo = MainConfig::alarmInformation;

  trackACount = alarmInfo->GetTrackACount();
  trackBCount = alarmInfo->GetTrackBCount();

  TRACE_FUNCTION_INT(trackACount);
  TRACE_FUNCTION_INT(trackBCount);
  
  trackAMissing = alarmInfo->GetTrackAMissingCount();
  trackBMissing = alarmInfo->GetTrackBMissingCount();

  alarmInfo->GetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                 totalMinorDiffer, trackMinorDiffer);
  combinedSignals = alarmInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(trackACount, trackBCount);
  statsWindow->SetMissingTrackCounts(trackAMissing, trackBMissing);
  statsWindow->SetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                   totalMinorDiffer, trackMinorDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);
}

