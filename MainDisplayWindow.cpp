/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : November 21 2023
 * PROJECT      : Signals Database
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
#include "MainDisplayWindow.h"

/*****************************************************************************!
 * Function : MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::MainDisplayWindow
() : QWidget()
{
  QPalette				pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(160, 160, 160)));
  setPalette(pal);
  setAutoFillBackground(true);

  Initialize();
}

/*****************************************************************************!
 * Function : ~MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::~MainDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainDisplayWindow::Initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MainDisplayWindow::InitializeSubWindows()
{
  tabWindow = NULL;  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  tabWindow = new SignalTabWindow();  
  tabWindow->setParent(this);

  alarmDisplayWindow = new AlarmDisplayWindow();
  controlDisplayWindow = new ControlDisplayWindow();
  equipmentDisplayWindow = new EquipmentDisplayWindow();
  sampleDisplayWindow = new SampleDisplayWindow();
  settingDisplayWindow = new SettingDisplayWindow();

  tabWindow->addTab(alarmDisplayWindow, "Alarm");
  tabWindow->addTab(controlDisplayWindow, "Control");
  tabWindow->addTab(equipmentDisplayWindow, "Equipment");
  tabWindow->addTab(sampleDisplayWindow, "Sample");
  tabWindow->addTab(settingDisplayWindow, "Settingr");
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
MainDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  if ( tabWindow ) {
    tabWindow->resize(width, height);
  }
}
