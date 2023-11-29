/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : November 21 2023
 * PROJECT      : Signals Database
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
#include "MainDisplayWindow.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define TABBAR_HEIGHT                   25

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
  CreateConnections();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MainDisplayWindow::InitializeSubWindows()
{
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  tabBar = new QTabBar(this);
  tabBar->move(0, 0);

  alarmDisplayWindow = new AlarmDisplayWindow("Alarms");
  alarmDisplayWindow->setParent(this);
  
  controlDisplayWindow = new ControlDisplayWindow("Control");
  controlDisplayWindow->setParent(this);
  
  equipmentDisplayWindow = new EquipmentDisplayWindow("Equipment");
  equipmentDisplayWindow->setParent(this);
  
  sampleDisplayWindow = new SampleDisplayWindow("Sample");
  sampleDisplayWindow->setParent(this);
  
  settingDisplayWindow = new SettingDisplayWindow("Setting");
  settingDisplayWindow->setParent(this);

  windows << alarmDisplayWindow;
  windows << controlDisplayWindow;
  windows << equipmentDisplayWindow;
  windows << sampleDisplayWindow;
  windows << settingDisplayWindow;

  alarmDisplayWindow->hide();
  controlDisplayWindow->hide();
  equipmentDisplayWindow->show();
  sampleDisplayWindow->hide();
  settingDisplayWindow->hide();
  
  tabBar->addTab("Alarm");
  tabBar->addTab("Control");
  tabBar->addTab("Equipment");
  tabBar->addTab("Sample");
  tabBar->addTab("Setting");
  tabBar->setCurrentIndex(2);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
MainDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   windowY;
  int                                   windowH;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  windowH = height - TABBAR_HEIGHT;
  windowY = TABBAR_HEIGHT;

  
  alarmDisplayWindow->resize(width, windowH);
  alarmDisplayWindow->move(0, windowY);

  controlDisplayWindow->resize(width, windowH);
  controlDisplayWindow->move(0, windowY);

  equipmentDisplayWindow->resize(width, windowH);
  equipmentDisplayWindow->move(0, windowY);

  sampleDisplayWindow->resize(width, windowH);
  sampleDisplayWindow->move(0, windowY);

  settingDisplayWindow->resize(width, windowH);
  settingDisplayWindow->move(0, windowY);

  tabBar->resize(width, TABBAR_HEIGHT);
}

/*****************************************************************************!
 * Function : SlotTabSelected
 *****************************************************************************/
void
MainDisplayWindow::SlotTabSelected
(int InTabIndex)
{
  HideWindows();
  windows[InTabIndex]->show();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
MainDisplayWindow::CreateConnections
()
{
  connect(tabBar,
          QTabBar::tabBarClicked,
          this,
          MainDisplayWindow::SlotTabSelected);
}

/*****************************************************************************!
 * Function : HideWindows
 *****************************************************************************/
void
MainDisplayWindow::HideWindows(void)
{
  alarmDisplayWindow->hide();
  controlDisplayWindow->hide();
  alarmDisplayWindow->hide();
  sampleDisplayWindow->hide();
  settingDisplayWindow->hide();
}
