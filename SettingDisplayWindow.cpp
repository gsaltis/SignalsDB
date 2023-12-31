/*****************************************************************************
 * FILE NAME    : SettingDisplayWindow.cpp
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
#include "SettingDisplayWindow.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : SettingDisplayWindow
 *****************************************************************************/
SettingDisplayWindow::SettingDisplayWindow
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
 * Function : ~SettingDisplayWindow
 *****************************************************************************/
SettingDisplayWindow::~SettingDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SettingDisplayWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  SetSettingInformation();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SettingDisplayWindow::CreateSubWindows()
{
  settingForm = new SettingDisplayForm();  
  settingForm->setParent(this);
}

/*****************************************************************************!
 * Function : SetSettingInformation
 *****************************************************************************/
void
SettingDisplayWindow::SetSettingInformation
()
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
  SettingInformation*                   settingInfo;
  
  settingInfo = MainConfig::settingInformation;

  trackACount = settingInfo->GetTrackACount();
  trackBCount = settingInfo->GetTrackBCount();

  trackAMissing = settingInfo->GetTrackAMissingCount();
  trackBMissing = settingInfo->GetTrackBMissingCount();

  settingInfo->GetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                   totalMinorDiffer, trackMinorDiffer);
  
  combinedSignals = settingInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(trackACount, trackBCount);
  statsWindow->SetMissingTrackCounts(trackAMissing, trackBMissing);
  statsWindow->SetTrackDifferCount(totalMajorDiffer, trackMajorDiffer,
                                   totalMinorDiffer, trackMinorDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SettingDisplayWindow::InitializeSubWindows()
{
  settingForm = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SettingDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;
  int                                   settingFormX;
  int                                   settingFormY;
  int                                   settingFormW;
  int                                   settingFormH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  settingFormX = 0;
  settingFormY = SIGNAL_STATS_WINDOW_HEIGHT;
  settingFormW = width;
  settingFormH = height - SIGNAL_STATS_WINDOW_HEIGHT;
  
  if ( statsWindow ) {
    statsWindow->resize(width, SIGNAL_STATS_WINDOW_HEIGHT);
  }
  if ( settingForm ) {
    settingForm->move(settingFormX, settingFormY);
    settingForm->resize(settingFormW, settingFormH);
  }
}

