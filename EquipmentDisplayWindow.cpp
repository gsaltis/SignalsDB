/*****************************************************************************
 * FILE NAME    : EquipmentDisplayWindow.cpp
 * DATE         : November 20 2023
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
#include "EquipmentDisplayWindow.h"
#include "MainConfig.h"

/*****************************************************************************!
 * Function : EquipmentDisplayWindow
 *****************************************************************************/
EquipmentDisplayWindow::EquipmentDisplayWindow
(QString InText) : SignalDisplayWindow(InText)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0xEC, 0xEC, 0xEC)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~EquipmentDisplayWindow
 *****************************************************************************/
EquipmentDisplayWindow::~EquipmentDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
EquipmentDisplayWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  SetEquipmentInformation();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
EquipmentDisplayWindow::CreateSubWindows()
{
  equipForm = new EquipmentDisplayForm();
  equipForm->setParent(this);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
EquipmentDisplayWindow::CreateConnections
()
{
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
EquipmentDisplayWindow::InitializeSubWindows()
{
  equipForm = NULL;
}

/*****************************************************************************!
 * Function : SetEquipmentInformation
 *****************************************************************************/
void
EquipmentDisplayWindow::SetEquipmentInformation
()
{
  int                                   combinedSignals;
  int                                   trackDiffer;
  int                                   track2Missing;
  int                                   track3Missing;
  int                                   track3Count;
  int                                   track2Count;

  EquipmentInfo = MainConfig::equipmentInformation;

  track2Count = EquipmentInfo->GetTrack2Count();
  track3Count = EquipmentInfo->GetTrack3Count();

  track2Missing = EquipmentInfo->GetTrack2MissingCount();
  track3Missing = EquipmentInfo->GetTrack3MissingCount();

  trackDiffer = EquipmentInfo->GetTrackDifferCount();
  combinedSignals = EquipmentInfo->GetPairCount();
  
  statsWindow->SetTrackCounts(track2Count, track3Count);
  statsWindow->SetMissingTrackCounts(track2Missing, track3Missing);
  statsWindow->SetTrackDifferCount(trackDiffer);
  statsWindow->SetCombinedSignalCount(combinedSignals);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
EquipmentDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;
  int                                   equipFormX;
  int                                   equipFormY;
  int                                   equipFormW;
  int                                   equipFormH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  equipFormX = 0;
  equipFormY = SIGNAL_STATS_WINDOW_HEIGHT;
  equipFormW = width;
  equipFormH = height - SIGNAL_STATS_WINDOW_HEIGHT;
  
  if ( statsWindow ) {
    statsWindow->resize(width, SIGNAL_STATS_WINDOW_HEIGHT);
  }
  if ( equipForm ) {
    equipForm->move(equipFormX, equipFormY);
    equipForm->resize(equipFormW, equipFormH);
  }
}

