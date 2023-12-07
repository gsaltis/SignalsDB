/*****************************************************************************
 * FILE NAME    : MainWindow.cpp
 * DATE         : November 21 2023
 * PROJECT      : Signals Database
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "main.h"

/*****************************************************************************!
 * Function : MainWindow
 *****************************************************************************/
MainWindow::MainWindow
(int InInitialTab) : QMainWindow(NULL)
{
  InitialTab = InInitialTab;
  Initialize();
  CreateActions();
  CreateMenus();
  InitializeSubWindows();
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : ~MainWindow
 *****************************************************************************/
MainWindow::~MainWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainWindow::Initialize()
{
  setWindowTitle(SystemConfig::SystemName);  
}

/*****************************************************************************!
 * Function : CreateSubWindows
 * Purpose  : Create Sub Windows
 *****************************************************************************/
void
MainWindow::CreateSubWindows()
{
  displayWindow = new MainDisplayWindow(InitialTab);
  displayWindow->setParent(this);
  statusbar = statusBar();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 * Purpose  : Create Sub Windows
 *****************************************************************************/
void
MainWindow::InitializeSubWindows()
{
  displayWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 * Purpose  : Handle Resize Event
 *****************************************************************************/
void
MainWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   width;
  int                                   height;
  QSize                                 size;
  QSize                                 statusbar_size;
  QSize                                 menu_size;
  size = InEvent->size();  
  menu_size = menubar->size();
  statusbar_size = statusbar->size();
  width = size.width();
  height = size.height() - (menu_size.height() + statusbar_size.height());
  if ( displayWindow ) {
    displayWindow->move(0, menu_size.height());
    displayWindow->resize(width, height);
  }

  MainSetMainWindowGeometry(pos(), size);
}

/*****************************************************************************!
 * Function : CreateActions
 * Purpose  : Create New Actions
 *****************************************************************************/
void
MainWindow::CreateActions()
{
  ActionExit = new QAction("E&xit", this);
  connect(ActionExit, SIGNAL(triggered()), this, SLOT(SlotExit()));
}

/*****************************************************************************!
 * Function : CreateMenus
 * Purpose  : Create New Menus
 *****************************************************************************/
void
MainWindow::CreateMenus()
{
  menubar = menuBar();  
  fileMenu = menubar->addMenu("&File");
  fileMenu->addAction(ActionExit);
}

/*****************************************************************************!
 * Function : SlotExit
 *****************************************************************************/
void
MainWindow::SlotExit(void)
{
  exit(EXIT_SUCCESS);  
}

/*****************************************************************************!
 * Function : moveEvent
 *****************************************************************************/
void
MainWindow::moveEvent
(QMoveEvent* InEvent)
{
  QPoint                                pos;
  pos = InEvent->pos();
  MainSetMainWindowGeometry(pos, size());
}
