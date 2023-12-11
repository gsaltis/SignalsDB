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
  ElementDisplayLine*                   lastLine;
  int                                   y2;
  int                                   x4;
  int                                   w2;
  QPoint                                p2;
  QSize					size;
  QSize                                 s2;
  int                                   h2;
  int					width;
  int					height;
  int                                   navigationWindowX;
  int                                   navigationWindowY;
  int                                   navigationWindowW;
  int                                   navigationWindowH;
  
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

  lastLine = NULL;
  for ( auto i : elementLines ) {
    i->resize(width, i->size().height());
    lastLine = i;
  }

  p2 = lastLine->pos();
  y2 = p2.y();
  s2 = lastLine->size();
  h2 = (height - (NAVIGATION_WINDOW_HEIGHT + y2));
        
  lastLine->resize(s2.width(), h2);
  
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
          NavigationWindow::SignalFirstElement,
          this,
          AlarmDisplayForm::SlotFirstElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalLastElement,
          this,
          AlarmDisplayForm::SlotLastElement);
  
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
AlarmDisplayForm::SlotNextElement
(int )
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
 * Function : SlotPreviousElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotPreviousElement
(int )
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
  int                                   n;
  QStringList                           keys;
  int                                   i;
  NCUAlarmSignal*                       track2;
  NCUAlarmSignal*                       track3;

  TRACE_FUNCTION_START();
  AlarmIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  keys = elementLines.keys();
  n = keys.size();
  for ( i = 0 ; i < n ; i++ ) {
    TRACE_FUNCTION_QSTRING(keys[i]);
    elementLines[keys[i]]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines["AlarmName"]->SetTrack2Value(track2->AlarmName);
    TRACE_FUNCTION_LOCATION();
    elementLines["Level"]->SetTrack2Value(track2->Level);
    TRACE_FUNCTION_LOCATION();
    elementLines["ExpRPN"]->SetTrack2Value(track2->ExpRPN);
    TRACE_FUNCTION_LOCATION();
    elementLines["ExpFull"]->SetTrack2Value(track2->EXPFull);
    TRACE_FUNCTION_LOCATION();
    elementLines["Delay"]->SetTrack2Value(track2->Delay);
    TRACE_FUNCTION_LOCATION();
    elementLines["SuppressRPN"]->SetTrack2Value(track2->SuppressRPN);
    TRACE_FUNCTION_LOCATION();
    elementLines["SuppressFull"]->SetTrack2Value(track2->SuppressFull);
    TRACE_FUNCTION_LOCATION();
    elementLines["Relay"]->SetTrack2Value(track2->Relay);
    TRACE_FUNCTION_LOCATION();
    elementLines["Help"]->SetTrack2Value(track2->Help);
    TRACE_FUNCTION_LOCATION();
  }

  if ( track3 ) {
    i = 0;
    elementLines["AlarmName"]->SetTrack3Value(track3->AlarmName);
    elementLines["Level"]->SetTrack3Value(track3->Level);
    elementLines["ExpRPN"]->SetTrack3Value(track3->ExpRPN);
    elementLines["ExpFull"]->SetTrack3Value(track3->EXPFull);
    elementLines["Delay"]->SetTrack3Value(track3->Delay);
    elementLines["SuppressRPN"]->SetTrack3Value(track3->SuppressRPN);
    elementLines["SuppressFull"]->SetTrack3Value(track3->SuppressFull);
    elementLines["Relay"]->SetTrack3Value(track3->Relay);
    elementLines["Help"]->SetTrack3Value(track3->Help);
  }

  keys = elementLines.keys();
  n = keys.size();
  for ( i = 0 ; i < n ; i++ ) {
    elementLines[keys[i]]->Compare();
  }
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotFirstElement(void)
{
  AlarmSignalPair*                  pair;
  currentEquipIndex = 0;
  pair = alarmInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentAlarmIndex(currentEquipIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotLastElement(void)
{
  AlarmSignalPair*                  pair;
  currentEquipIndex = alarmInformation->GetPairCount() - 1;
  pair = alarmInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentAlarmIndex(currentEquipIndex + 1);  

}
