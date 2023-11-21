/*****************************************************************************
 * FILE NAME    : SignalStatsWindow.cpp
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
#include "SignalStatsWindow.h"

/*****************************************************************************!
 * Function : SignalStatsWindow
 *****************************************************************************/
SignalStatsWindow::SignalStatsWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SignalStatsWindow
 *****************************************************************************/
SignalStatsWindow::~SignalStatsWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SignalStatsWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SignalStatsWindow::CreateSubWindows()
{
  int                                   labelWidth2;
  int                                   x, x1, x2;
  int                                   y;
  int                                   labelWidth;
  int                                   labelHeight;

  
  x = 10;
  y = 10;
  labelWidth = 120;
  labelWidth2 = 80;
  labelHeight = 15;
  
  x1 = x + labelWidth + 10;
  x2 = x1 + labelWidth2 + 10;

  CreateSimpleLabel("Track 2", x1, y, labelWidth2, labelHeight);
  CreateSimpleLabel("Track 3", x2, y, labelWidth2, labelHeight);
  y += labelHeight + 10;

  CreateSimpleLabel("Total Signals", x, y, labelWidth, labelHeight);
  Track2TotalLabel = CreateDisplayLabel(x1, y, labelWidth2, labelHeight);
  Track3TotalLabel = CreateDisplayLabel(x2, y, labelWidth2, labelHeight);
  y += labelHeight + 10;

  CreateSimpleLabel("Missing Signals", x, y, labelWidth, labelHeight);
  Track2MissingLabel = CreateDisplayLabel(x1, y, labelWidth2, labelHeight);
  Track3MissingLabel = CreateDisplayLabel(x2, y, labelWidth2, labelHeight);
  y += labelHeight + 10;

  CreateSimpleLabel("Differing Signals", x, y, labelWidth, labelHeight);
  Track2DifferLabel = CreateDisplayLabel(x1, y, labelWidth2, labelHeight);
  Track3DifferLabel = CreateDisplayLabel(x2, y, labelWidth2, labelHeight);
  y += labelHeight + 10;
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SignalStatsWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SignalStatsWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : CreateSimpleLabel
 *****************************************************************************/
void
SignalStatsWindow::CreateSimpleLabel
(QString InText, int InX, int InY, int InWidth, int InHeight)
{
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  QLabel*                               label;
  QPalette                              pal;
  
  label = new QLabel();
  label->setParent(this);
  label->move(InX, InY);
  label->resize(InWidth, InHeight);
  label->setText(InText);
  label->setAlignment(Qt::AlignRight);
  label->setFont(labelFont);

  pal = label->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 0, 0)));
  label->setPalette(pal);
  label->setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : CreateDisplayLabel
 *****************************************************************************/
QLabel*
SignalStatsWindow::CreateDisplayLabel
(int InX, int InY, int InWidth, int InHeight)
{
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Normal);
  QLabel*                               label;
  QPalette                              pal;
  
  label = new QLabel();
  label->setParent(this);
  label->move(InX, InY);
  label->resize(InWidth, InHeight);
  label->setText("0");
  label->setAlignment(Qt::AlignRight);
  label->setFont(labelFont);

  pal = label->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 0, 0)));
  label->setPalette(pal);
  label->setAutoFillBackground(true);
  
  return label;
}

/*****************************************************************************!
 * Function : SlotSetTrack2Totals
 *****************************************************************************/
void
SignalStatsWindow::SlotSetTrack2Totals
(int InSignals)
{
  Track2TotalSignals = InSignals;
}

/*****************************************************************************!
 * Function : SlotSetTrack3Totals
 *****************************************************************************/
void
SignalStatsWindow::SlotSetTrack3Totals
(int InSignals)
{
  Track3TotalSignals = InSignals;  
}

/*****************************************************************************!
 * Function : SlotSetTrack2Differs
 *****************************************************************************/
void
SignalStatsWindow::SlotSetTrack2Differs
(int InSignals)
{
  Track2DifferSignals = InSignals;  
}

/*****************************************************************************!
 * Function : SlotSetTrack3Differs
 *****************************************************************************/
void
SignalStatsWindow::SlotSetTrack3Differs
(int InSignals)
{
  Track3DifferSignals = InSignals;  
}

/*****************************************************************************!
 * Function : SlotSetTrack2Missing
 *****************************************************************************/
void
SignalStatsWindow::SlotSetTrack2Missing
(int InSignals)
{
  Track2MissingSignals = InSignals;    
}

/*****************************************************************************!
 * Function : SlotSetTrack3Missing
 *****************************************************************************/
void
SignalStatsWindow::SlotSetTrack3Missing
(int InSignals)
{
  Track3MissingSignals = InSignals;      
}
