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
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
AlarmDisplayWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
AlarmDisplayWindow::InitializeSubWindows()
{
  
}

