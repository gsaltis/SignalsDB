/*****************************************************************************
 * FILE NAME    : ControlDisplayWindow.cpp
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
#include "ControlDisplayWindow.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : ControlDisplayWindow
 *****************************************************************************/
ControlDisplayWindow::ControlDisplayWindow
(QString InText) : SignalDisplayWindow(InText)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(192, 192, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~ControlDisplayWindow
 *****************************************************************************/
ControlDisplayWindow::~ControlDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
ControlDisplayWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  SetControlInformation();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
ControlDisplayWindow::CreateSubWindows()
{
  controlForm = new ControlDisplayForm();
  controlForm->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
ControlDisplayWindow::InitializeSubWindows()
{
  controlForm = NULL;
}

/*****************************************************************************!
 * Function : SetControlInformation
 *****************************************************************************/
void
ControlDisplayWindow::SetControlInformation
()
{
  int                                   combinedSignals;
  int                                   trackDiffer;
  int                                   track2Missing;
  int                                   track3Missing;
  int                                   track3Count;
  int                                   track2Count;

  controlInfo = MainConfig::controlInformation;

  track2Count = controlInfo->GetTrack2Count();
  track3Count = controlInfo->GetTrack3Count();

  track2Missing = controlInfo->GetTrack2MissingCount();
  track3Missing = controlInfo->GetTrack3MissingCount();

  trackDiffer = controlInfo->GetTrackDifferCount();
  combinedSignals = controlInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(track2Count, track3Count);
  statsWindow->SetMissingTrackCounts(track2Missing, track3Missing);
  statsWindow->SetTrackDifferCount(trackDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
ControlDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;
  int                                   controlFormX;
  int                                   controlFormY;
  int                                   controlFormW;
  int                                   controlFormH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  controlFormX = 0;
  controlFormY = SIGNAL_STATS_WINDOW_HEIGHT;
  controlFormW = width;
  controlFormH = height - SIGNAL_STATS_WINDOW_HEIGHT;
  
  if ( statsWindow ) {
    statsWindow->resize(width, SIGNAL_STATS_WINDOW_HEIGHT);
  }
  if ( controlForm ) {
    controlForm->move(controlFormX, controlFormY);
    controlForm->resize(controlFormW, controlFormH);
  }
}

