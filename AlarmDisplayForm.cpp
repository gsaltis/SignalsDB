/*****************************************************************************
 * FILE NAME    : AlarmDisplayForm.cpp
 * DATE         : November 22 2023
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
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "AlarmDisplayForm.h"
#include "ElementDisplayLine.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : AlarmDisplayForm
 *****************************************************************************/
AlarmDisplayForm::AlarmDisplayForm
() : SignalDisplayForm()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0xEC, 0xEC, 0xEC)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~AlarmDisplayForm
 *****************************************************************************/
AlarmDisplayForm::~AlarmDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
AlarmDisplayForm::initialize()
{
  AlarmSignalPair*                      pair;

  TRACE_FUNCTION_START();
  currentEquipIndex = 0;
  alarmInformation = MainConfig::alarmInformation;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  pair = alarmInformation->GetPairByIndex(0);
  SetTrackInformation(pair);
  navigationWindow->SlotSetCurrentSignalIndex(1);
  navigationWindow->SlotSetSignalCount(alarmInformation->GetPairCount());
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
AlarmDisplayForm::CreateSubWindows()
{
  int                                   headingLabelHeight;
  QLabel*                               label;
  int                                   x1, x2, x3;
  int                                   y;
  int                                   labelWidth = 210;
  int                                   labelHeight = 20;
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  QFont                                 valueFont = QFont("Segoe UI", 10, QFont::Normal);
  
  x1 = 10;
  x2 = x1 + labelWidth + 20;
  x3 = x2 + labelWidth + 20;
  headingLabelHeight = 25;

  y = 30;
  
  //!
  y = 10;
  label = new QLabel();
  label->setParent(this);
  label->move(x1, y);
  label->resize(225, labelHeight);
  label->setFont(labelFont);
  label->setText(QString("Alarm ID : "));
  label->setAlignment(Qt::AlignRight);

  AlarmIDLabel = new QLabel(this);
  AlarmIDLabel->move(x1 + 230, y);
  AlarmIDLabel->resize(80, labelHeight);
  AlarmIDLabel->setAlignment(Qt::AlignLeft);
  AlarmIDLabel->setFont(valueFont);

  y += labelHeight;
  label = new QLabel();
  label->setParent(this);
  label->move(x1, y);
  label->resize(225, labelHeight);
  label->setFont(labelFont);
  label->setText(QString("Signal ID : "));
  label->setAlignment(Qt::AlignRight);

  SignalIDLabel = new QLabel(this);
  SignalIDLabel->move(x1 + 230, y);
  SignalIDLabel->resize(80, labelHeight);
  SignalIDLabel->setAlignment(Qt::AlignLeft);
  SignalIDLabel->setFont(valueFont);

  //!
  y += labelHeight + 5;
  label = new QLabel();
  label->setParent(this);
  label->move(x2, y);
  label->resize(labelWidth, headingLabelHeight);
  label->setFont(labelFont);
  label->setText(QString("TRACK 2"));
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  
  label = new QLabel();
  label->setParent(this);
  label->move(x3, y);
  label->resize(labelWidth, headingLabelHeight);
  label->setFont(labelFont);
  label->setText(QString("TRACK 3"));
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  Track3Label = label;
  
  
  //!
  y += headingLabelHeight;
  AddElementLines("Alarm", y);

  navigationWindow = new NavigationWindow();
  navigationWindow->move(10, y);
  navigationWindow->resize(labelWidth + 20, NAVIGATION_WINDOW_HEIGHT);
  navigationWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
AlarmDisplayForm::InitializeSubWindows()
{
  navigationWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
AlarmDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   y2;
  int                                   x4;
  int                                   w2;
  QPoint                                p2;
  int                                   n;
  QSize					size;
  QSize                                 s2;
  int                                   h2;
  int					width;
  int					height;
  int                                   navigationWindowX;
  int                                   navigationWindowY;
  int                                   navigationWindowW;
  int                                   navigationWindowH;
  ElementDisplayLine*                   line;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  w2 = width - 110;
  w2 /= 2;
  x4 = 175 + w2;

  navigationWindowX = 0;
  navigationWindowY = height - NAVIGATION_WINDOW_HEIGHT;
  navigationWindowW = width;
  navigationWindowH = NAVIGATION_WINDOW_HEIGHT;
  
  Track3Label->move(x4, Track3Label->pos().y());
  
  for ( auto i : elementLines ) {
    i->resize(width, i->size().height());
  }

  n = elementLines.size() - 1;
  line = elementLines[n];
  p2 = line->pos();
  y2 = p2.y();
  s2 = line->size();

  TRACE_FUNCTION_INT(y2);
  TRACE_FUNCTION_INT(height);
  h2 = (height - (NAVIGATION_WINDOW_HEIGHT + y2));
  TRACE_FUNCTION_INT(h2);
        
  line->resize(s2.width(), h2);
  
  if ( navigationWindow ) {
    navigationWindow->move(navigationWindowX, navigationWindowY);
    navigationWindow->resize(navigationWindowW, navigationWindowH);
  }
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
AlarmDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalNextDifferElement,
          this,
          AlarmDisplayForm::SlotNextDifferElement);
  connect(navigationWindow,
          NavigationWindow::SignalPrevDifferElement,
          this,
          AlarmDisplayForm::SlotPrevDifferElement);
  connect(navigationWindow,
          NavigationWindow::SignalNextElement,
          this,
          AlarmDisplayForm::SlotNextElement);
  connect(navigationWindow,
          NavigationWindow::SignalPreviousElement,
          this,
          AlarmDisplayForm::SlotPreviousElement);
  connect(this,
          AlarmDisplayForm::SignalSetCurrentAlarmIndex,
          navigationWindow,
          NavigationWindow::SlotSetCurrentSignalIndex);
}

/*****************************************************************************!
 * Function : SlotNextElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotNextElement(void)
{
  AlarmSignalPair*                      pair;
  if ( currentEquipIndex + 1 >= alarmInformation->GetPairCount() ) {
    return;
  }

  currentEquipIndex++;
  pair = alarmInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentAlarmIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SlotNextDifferElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotNextDifferElement(void)
{
  int                                   i, n;
  AlarmSignalPair*                      pair;
  
  n = alarmInformation->GetPairCount();

  for ( i = currentEquipIndex + 1 ; i < n ; i++ ) {
    pair = alarmInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentAlarmIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPrevDifferElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotPrevDifferElement(void)
{
  int                                   i;
  AlarmSignalPair*                      pair;
  
  for ( i = currentEquipIndex - 1; i >= 0 ; i-- ) {
    pair = alarmInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentAlarmIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotPreviousElement(void)
{
  AlarmSignalPair*                  pair;
  if ( currentEquipIndex == 0 ) {
    return;
  }
  currentEquipIndex--;
  pair = alarmInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
    emit SignalSetCurrentAlarmIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
AlarmDisplayForm::SetTrackInformation
(AlarmSignalPair* InPair)
{
  
  int                                   i;
  NCUAlarmSignal*                       track2;
  NCUAlarmSignal*                       track3;

  AlarmIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines[i++]->SetTrack2Value(track2->AlarmName);
    elementLines[i++]->SetTrack2Value(track2->Level);
    elementLines[i++]->SetTrack2Value(track2->ExpRPN);
    elementLines[i++]->SetTrack2Value(track2->EXPFull);
    elementLines[i++]->SetTrack2Value(track2->Delay);
    elementLines[i++]->SetTrack2Value(track2->SuppressRPN);
    elementLines[i++]->SetTrack2Value(track2->SuppressFull);
    elementLines[i++]->SetTrack2Value(track2->Relay);
    elementLines[i++]->SetTrack2Value(track2->Help);
  }

  if ( track3 ) {
    i = 0;
    elementLines[i++]->SetTrack3Value(track3->AlarmName);
    elementLines[i++]->SetTrack3Value(track3->Level);
    elementLines[i++]->SetTrack3Value(track3->ExpRPN);
    elementLines[i++]->SetTrack3Value(track3->EXPFull);
    elementLines[i++]->SetTrack3Value(track3->Delay);
    elementLines[i++]->SetTrack3Value(track3->SuppressRPN);
    elementLines[i++]->SetTrack3Value(track3->SuppressFull);
    elementLines[i++]->SetTrack3Value(track3->Relay);
    elementLines[i++]->SetTrack3Value(track3->Help);
  }

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Compare();
  }

}
