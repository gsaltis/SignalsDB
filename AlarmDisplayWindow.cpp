/*****************************************************************************
 * FILE NAME    : AlarmDisplayWindow.cpp
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
  int                                   track2Missing;
  int                                   track3Missing;
  int                                   track3Count;
  int                                   track2Count;

  alarmInfo = MainConfig::alarmInformation;

  track2Count = alarmInfo->GetTrack2Count();
  track3Count = alarmInfo->GetTrack3Count();

  track2Missing = alarmInfo->GetTrack2MissingCount();
  track3Missing = alarmInfo->GetTrack3MissingCount();

  alarmInfo->GetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                 totalMinorDiffer, trackMinorDiffer);
  combinedSignals = alarmInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(track2Count, track3Count);
  statsWindow->SetMissingTrackCounts(track2Missing, track3Missing);
  statsWindow->SetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                   totalMinorDiffer, trackMinorDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);
}

