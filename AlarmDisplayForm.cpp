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
  int                                   pairCount;
  
  currentAlarmIndex = 0;
  alarmInformation = MainConfig::alarmInformation;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  pairCount = alarmInformation->GetPairCount();
  TRACE_FUNCTION_INT(pairCount);
  pair = alarmInformation->GetPairByIndex(0);
  SetTrackInformation(pair);
  navigationWindow->SlotSetCurrentSignalIndex(1);
  navigationWindow->SlotSetSignalCount(alarmInformation->GetPairCount());
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
  label->setText(QString("Alarm ID"));
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
  label->setText(QString("Signal ID"));
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
  label->setText(QString("TRACK %1").arg(MainTrackAID->GetNumber()));
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  
  label = new QLabel();
  label->setParent(this);
  label->move(x3, y);
  label->resize(labelWidth, headingLabelHeight);
  label->setFont(labelFont);
  label->setText(QString("TRACK %1").arg(MainTrackBID->GetNumber()));
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  TrackBLabel = label;
  
  
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
  
  TrackBLabel->move(x4, TrackBLabel->pos().y());

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
 * Function : SetTrackInformation
 *****************************************************************************/
void
AlarmDisplayForm::SetTrackInformation
(AlarmSignalPair* InPair)
{
  int                                   n;
  QStringList                           keys;
  int                                   i;
  NCUAlarmSignal*                       trackA;
  NCUAlarmSignal*                       trackB;

  AlarmIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  trackA = InPair->GetTrackA();
  trackB = InPair->GetTrackB();

  keys = elementLines.keys();
  n = keys.size();
  for ( i = 0 ; i < n ; i++ ) {
    elementLines[keys[i]]->Clear();
  }

  if ( trackA ) {
    i = 0;
    elementLines["AlarmName"]->SetTrackAValue(trackA->GetValue("AlarmName"));
    elementLines["Level"]->SetTrackAValue(trackA->GetValue("Level"));
    elementLines["ExpRPN"]->SetTrackAValue(trackA->GetValue("ExpRPN"));
    elementLines["ExpFull"]->SetTrackAValue(trackA->GetValue("EXPFull"));
    elementLines["Delay"]->SetTrackAValue(trackA->GetValue("Delay"));
    elementLines["SuppressRPN"]->SetTrackAValue(trackA->GetValue("SuppressRPN"));
    elementLines["SuppressFull"]->SetTrackAValue(trackA->GetValue("SuppressFull"));
    elementLines["Relay"]->SetTrackAValue(trackA->GetValue("Relay"));
    elementLines["Help"]->SetTrackAValue(trackA->GetValue("Help"));
  }

  if ( trackB ) {
    i = 0;
    elementLines["AlarmName"]->SetTrackBValue(trackB->GetValue("AlarmName"));
    elementLines["Level"]->SetTrackBValue(trackB->GetValue("Level"));
    elementLines["ExpRPN"]->SetTrackBValue(trackB->GetValue("ExpRPN"));
    elementLines["ExpFull"]->SetTrackBValue(trackB->GetValue("EXPFull"));
    elementLines["Delay"]->SetTrackBValue(trackB->GetValue("Delay"));
    elementLines["SuppressRPN"]->SetTrackBValue(trackB->GetValue("SuppressRPN"));
    elementLines["SuppressFull"]->SetTrackBValue(trackB->GetValue("SuppressFull"));
    elementLines["Relay"]->SetTrackBValue(trackB->GetValue("Relay"));
    elementLines["Help"]->SetTrackBValue(trackB->GetValue("Help"));
  }

  keys = elementLines.keys();
  n = keys.size();
  for ( i = 0 ; i < n ; i++ ) {
    elementLines[keys[i]]->Compare();
  }
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotFirstElement(void)
{
  AlarmSignalPair*                  pair;
  currentAlarmIndex = 0;
  pair = alarmInformation->GetPairByIndex(currentAlarmIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentAlarmIndex(currentAlarmIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotLastElement(void)
{
  AlarmSignalPair*                  pair;
  currentAlarmIndex = alarmInformation->GetPairCount() - 1;
  pair = alarmInformation->GetPairByIndex(currentAlarmIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentAlarmIndex(currentAlarmIndex + 1);  

}

/*****************************************************************************!
 * Function : SlotNextElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotNextElement
(int InMajorMinorFlags )
{
  AlarmSignalPair*                      pair;
  if ( currentAlarmIndex + 1 >= alarmInformation->GetPairCount() ) {
    return;
  }

  if ( InMajorMinorFlags == 0 ) {
    currentAlarmIndex++;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToNextMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToNextMinorSignal();
  } else if ( (InMajorMinorFlags & NAVIGATION_ONLY3_FLAG) || (InMajorMinorFlags & NAVIGATION_ONLY2_FLAG) ) {
    SkipToNextMissingSignal(InMajorMinorFlags);
  } else {
    SkipToNextAnySignal();
  }
  pair = alarmInformation->GetPairByIndex(currentAlarmIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentAlarmIndex(currentAlarmIndex + 1);
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
AlarmDisplayForm::SlotPreviousElement
(int InMajorMinorFlags)
{
  AlarmSignalPair*                  pair;
  if ( currentAlarmIndex == 0 ) {
    return;
  }
  if ( InMajorMinorFlags == 0 ) {
    currentAlarmIndex--;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToPrevMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToPrevMinorSignal();
  } else if ( (InMajorMinorFlags & NAVIGATION_ONLY3_FLAG) || (InMajorMinorFlags & NAVIGATION_ONLY2_FLAG) ) {
    SkipToPrevMissingSignal(InMajorMinorFlags);
  } else {
    SkipToPrevAnySignal();
  }
  pair = alarmInformation->GetPairByIndex(currentAlarmIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentAlarmIndex(currentAlarmIndex + 1);
}

/*****************************************************************************!
 * Function : PairContainsMajorAlarm
 *****************************************************************************/
bool
AlarmDisplayForm::PairContainsMajorAlarm
(AlarmSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Major);
}

/*****************************************************************************!
 * Function : PairContainsMinorAlarm
 *****************************************************************************/
bool
AlarmDisplayForm::PairContainsMinorAlarm
(AlarmSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Minor);
}

/*****************************************************************************!
 * Function : PairContainsAlarm
 *****************************************************************************/
bool
AlarmDisplayForm::PairContainsAlarm
(AlarmSignalPair* InPair, ElementDisplayLine::DifferLevel InDifferType)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUAlarmSignal::Tags ) {
    if ( ! InPair->Differ(tag) ) {
     continue;
    }
    displayLine = elementLines[tag];
    if ( ! displayLine->isVisible() ) {
      continue;
    }
    differType = displayLine->GetDifferType();
    if ( differType == InDifferType ) {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : PairContainsAnyAlarm
 *****************************************************************************/
bool
AlarmDisplayForm::PairContainsAnyAlarm
(AlarmSignalPair* InPair)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUAlarmSignal::Tags ) {
    if ( ! InPair->Differ(tag) ) {
     continue;
    }
    displayLine = elementLines[tag];
    if ( ! displayLine->isVisible() ) {
      continue;
    }
    differType = displayLine->GetDifferType();
    if ( differType == ElementDisplayLine::Minor || differType == ElementDisplayLine::Major ) {
      return true;
    }
  }
  return false;
}

/*****************************************************************************!
 * Function : SkipToPrevMajorSignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToPrevMajorSignal(void)
{
  int                                   n;
  AlarmSignalPair*                      pair;

  currentAlarmIndex--;
  for ( n = currentAlarmIndex ; n > 0 ; n-- ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevMinorSignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToPrevMinorSignal(void)
{
  int                                   n;
  AlarmSignalPair*                      pair;

  currentAlarmIndex--;
  for ( n = currentAlarmIndex ; n > 0 ; n-- ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevAnySignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToPrevAnySignal(void)
{
  int                                   n;
  AlarmSignalPair*                      pair;

  currentAlarmIndex--;
  for ( n = currentAlarmIndex ; n > 0 ; n-- ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMajorSignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToNextMajorSignal
()
{
  int                                   n;
  int                                   m;
  AlarmSignalPair*                      pair;

  currentAlarmIndex++;
  m = alarmInformation->GetPairCount();
  for ( n = currentAlarmIndex ; n + 1 < m ; n++ ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMinorSignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToNextMinorSignal
()
{
  int                                   n;
  int                                   m;
  AlarmSignalPair*                      pair;

  currentAlarmIndex++;
  m = alarmInformation->GetPairCount();
  for ( n = currentAlarmIndex ; n + 1 < m ; n++ ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextAnySignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToNextAnySignal
()
{
  int                                   n;
  int                                   m;
  AlarmSignalPair*                      pair;

  currentAlarmIndex++;
  m = alarmInformation->GetPairCount();
  for ( n = currentAlarmIndex ; n + 1 < m ; n++ ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMissingSignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToNextMissingSignal
(int InMissingTracks)
{
  int                                   n;
  int                                   m;
  AlarmSignalPair*                      pair;

  currentAlarmIndex++;
  m = alarmInformation->GetPairCount();
  for ( n = currentAlarmIndex ; n + 1 < m ; n++ ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( InMissingTracks == NAVIGATION_ONLY3_FLAG ) {
      if ( pair->GetTrackA() == NULL ) {
        currentAlarmIndex = n;
        return;
      }
      continue;
    }
    if ( InMissingTracks == NAVIGATION_ONLY2_FLAG ) {
      if ( pair->GetTrackB() == NULL ) {
        currentAlarmIndex = n;
        return;
      }
      continue;
    }
    if ( pair->GetTrackA() == NULL || pair->GetTrackB() == NULL ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;  
}

/*****************************************************************************!
 * Function : SkipToPrevMissingSignal
 *****************************************************************************/
void
AlarmDisplayForm::SkipToPrevMissingSignal
(int InMissingTracks)
{
  int                                   n;
  AlarmSignalPair*                      pair;

  currentAlarmIndex--;
  for ( n = currentAlarmIndex ; n > 0 ; n-- ) {
    pair = alarmInformation->GetPairByIndex(n);
    if ( InMissingTracks == NAVIGATION_ONLY3_FLAG ) {
      if ( pair->GetTrackA() == NULL ) {
        currentAlarmIndex = n;
        return;
      }
      continue;
    }
    if ( InMissingTracks == NAVIGATION_ONLY2_FLAG ) {
      if ( pair->GetTrackB() == NULL ) {
        currentAlarmIndex = n;
        return;
      }
      continue;
    }
    if ( pair->GetTrackA() == NULL || pair->GetTrackB() == NULL ) {
      currentAlarmIndex = n;
      return;
    }
  }
  currentAlarmIndex = n;
}

