/*****************************************************************************
 * FILE NAME    : SignalStatsWindow.cpp
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
#include "SignalStatsWindow.h"
#include "main.h"

/*****************************************************************************!
 * Function : SignalStatsWindow
 *****************************************************************************/
SignalStatsWindow::SignalStatsWindow
(QString InText) : QWidget()
{

  text = InText;
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
  QString                               trackAName;
  QString                               trackBName;
  int                                   labelWidth2;
  int                                   x0, x1, x2, x3, x4, x5;
  int                                   y;
  int                                   labelWidth;
  int                                   labelHeight;
  
  y = WINDOW_HEADER_HEIGHT;

  labelWidth = 100;
  labelWidth2 = 200;
  
  labelHeight = 20;
  

  x0 = 35;
  x1 = labelWidth2 + 10;
  x2 = x1 + labelWidth + 10;
  x3 = x2 + labelWidth + 10;;
  x4 = x3 + labelWidth + 10;;
  x5 = x4 + labelWidth + 10;;
  

  CreateSimpleLabel("TOTAL",     x1, y, labelWidth, labelHeight);
  CreateSimpleLabel("MISSING",   x2, y, labelWidth, labelHeight);
  CreateSimpleLabel("MAJOR DIFFER", x3, y, labelWidth, labelHeight);
  CreateSimpleLabel("MINOR DIFFER", x4, y, labelWidth, labelHeight);
  CreateSimpleLabel("COMBINED",  x5, y, labelWidth, labelHeight);
  y += labelHeight;

  trackAName = QString("TRACK A (%1)").arg(MainTrackAID->ToString());
  trackBName = QString("TRACK B (%1)").arg(MainTrackBID->ToString());
  TRACE_FUNCTION_QSTRING(trackAName);
  TRACE_FUNCTION_QSTRING(trackBName);
  
  CreateSimpleLabel(trackAName, x0, y, labelWidth2, labelHeight);
  Track2TotalLabel = CreateDisplayLabel(x1, y, labelWidth, labelHeight);
  Track2MissingLabel = CreateDisplayLabel(x2, y, labelWidth, labelHeight);
  TrackMajorDifferLabel = CreateDisplayLabel(x3, y, labelWidth, labelHeight);
  TrackMinorDifferLabel = CreateDisplayLabel(x4, y, labelWidth, labelHeight);
  CombinedSignalsLabel = CreateDisplayLabel(x5, y, labelWidth, labelHeight);
  y += labelHeight;

  CreateSimpleLabel(trackBName, x0, y, labelWidth2, labelHeight);
  Track3TotalLabel = CreateDisplayLabel(x1, y, labelWidth, labelHeight);
  Track3MissingLabel = CreateDisplayLabel(x2, y, labelWidth, labelHeight);
  
  header = new WindowHeader(text, this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SignalStatsWindow::InitializeSubWindows()
{
  header = NULL;  
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

  size = InEvent->size();
  width = size.width();
  if ( header ) {
    header->resize(width, WINDOW_HEADER_HEIGHT);
  }
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

/*****************************************************************************!
 * Function : SlotSetTrack3Missing
 *****************************************************************************/
void
SignalStatsWindow::SlotSetCombinedSignals
(int InSignals)
{
  CombinedSignals = InSignals;      
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
SignalStatsWindow::paintEvent
(QPaintEvent*)
{
  QPainter                              painter(this);
  QSize                                 s = size();
  QRect                                 r = QRect(QPoint(0, 0), s);
  QPoint                                p1 = QPoint(0, 0);
  QPoint                                p2 = QPoint(0, s.height());
  QLinearGradient                       grad = QLinearGradient(p1, p2);
  QPen                                  pen = QPen(QColor(0xB0, 0xB0, 0xB0), 2);
  
  grad.setColorAt(0, QColor(0xB4, 0xB4, 0xB4));
  grad.setColorAt(1, QColor(0xEC, 0xEC, 0xEC));
  QBrush                                brush(grad);
  
  painter.setBrush(brush);
  painter.drawRect(r);

  painter.setPen(pen);
  painter.drawLine(0, s.height(), s.width(), s.height());
}

/*****************************************************************************!
 * Function : SetTrackCounts
 *****************************************************************************/
void
SignalStatsWindow::SetTrackCounts
(int InTrack2Count, int InTrack3Count)
{
  Track2TotalLabel->setText(QString("%1").arg(InTrack2Count));
  Track3TotalLabel->setText(QString("%1").arg(InTrack3Count));
}

/*****************************************************************************!
 * Function : SetMissingTrackCounts
 *****************************************************************************/
void
SignalStatsWindow::SetMissingTrackCounts
(int InTrack2Count, int InTrack3Count)
{
  Track2MissingLabel->setText(QString("%1").arg(InTrack2Count));
  Track3MissingLabel->setText(QString("%1").arg(InTrack3Count));
}

/*****************************************************************************!
 * Function : SetTrackDifferCount
 *****************************************************************************/
void
SignalStatsWindow::SetTrackDifferCount
(int InMajorCount, int InMinorCount)
{
  TrackMajorDifferLabel->setText(QString("%1").arg(InMajorCount));
  TrackMinorDifferLabel->setText(QString("%1").arg(InMinorCount));
}

/*****************************************************************************!
 * Function : SetTrackDifferCount
 *****************************************************************************/
void
SignalStatsWindow::SetTrackDifferCount
(int InTotalMajor, int InMajorCount, int InTotalMinor, int InMinorCount)
{
  TrackMajorDifferLabel->setText(QString("%1/%2").arg(InTotalMajor).arg(InMajorCount));
  TrackMinorDifferLabel->setText(QString("%1/%2").arg(InTotalMinor).arg(InMinorCount));
}

/*****************************************************************************!
 * Function : SetCombinedSignalCount
 *****************************************************************************/
void
SignalStatsWindow::SetCombinedSignalCount
(int InDifferCount)
{
  CombinedSignalsLabel->setText(QString("%1").arg(InDifferCount));
}
