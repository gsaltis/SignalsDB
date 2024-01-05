/*****************************************************************************
 * FILE NAME    : ControlDisplayForm.cpp
 * DATE         : November 22 2023
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
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "ControlDisplayForm.h"
#include "ElementDisplayLine.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : ControlDisplayForm
 *****************************************************************************/
ControlDisplayForm::ControlDisplayForm
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
 * Function : ~ControlDisplayForm
 *****************************************************************************/
ControlDisplayForm::~ControlDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
ControlDisplayForm::initialize()
{
  ControlSignalPair*                  pair;

  currentControlIndex = 0;
  controlInformation = MainConfig::controlInformation;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  pair = controlInformation->GetPairByIndex(0);
  SetTrackInformation(pair);
  navigationWindow->SlotSetCurrentSignalIndex(1);
  navigationWindow->SlotSetSignalCount(controlInformation->GetPairCount());
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
ControlDisplayForm::CreateSubWindows()
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
  label->setText(QString("Control ID"));
  label->setAlignment(Qt::AlignRight);

  ControlIDLabel = new QLabel(this);
  ControlIDLabel->move(x1 + 230, y);
  ControlIDLabel->resize(80, labelHeight);
  ControlIDLabel->setAlignment(Qt::AlignLeft);
  ControlIDLabel->setFont(valueFont);

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
  label->setText(QString("TRACK 2"));
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  
  label = new QLabel();
  label->setParent(this);
  label->move(x3, y);
  label->resize(labelWidth, headingLabelHeight);
  label->setFont(labelFont);
  label->setText(QString("TRACK 3"));
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  TrackBLabel = label;
  
  
  //!
  y += headingLabelHeight;
  AddElementLines("Control", y);
  
  navigationWindow = new NavigationWindow();
  navigationWindow->move(10, y);
  navigationWindow->resize(labelWidth + 20, NAVIGATION_WINDOW_HEIGHT);
  navigationWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
ControlDisplayForm::InitializeSubWindows()
{
  navigationWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
ControlDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
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
  ElementDisplayLine*                   lastLine;
  
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
    i->resize(width, ELEMENT_DISPLAY_LINE_HEIGHT);
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
ControlDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalFirstElement,
          this,
          ControlDisplayForm::SlotFirstElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalLastElement,
          this,
          ControlDisplayForm::SlotLastElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalNextElement,
          this,
          ControlDisplayForm::SlotNextElement);

  connect(navigationWindow,
          NavigationWindow::SignalPreviousElement,
          this,
          ControlDisplayForm::SlotPreviousElement);

  connect(this,
          ControlDisplayForm::SignalSetCurrentControlIndex,
          navigationWindow,
          NavigationWindow::SlotSetCurrentSignalIndex);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
ControlDisplayForm::SetTrackInformation
(ControlSignalPair* InPair)
{
  int                                   keysSize;
  QStringList                           keys;
  
  int                                   i;
  NCUControlSignal*                     trackA;
  NCUControlSignal*                     trackB;

  ControlIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  trackA = InPair->GetTrackA();
  trackB = InPair->GetTrackB();

  keys = elementLines.keys();
  keysSize  = keys.size();
  for ( i = 0 ; i < keysSize ; i ++) {
    elementLines[keys[i]]->Clear();
  }

  if ( trackA ) {
    for (i = 0; i < keysSize; i++) {
      elementLines[keys[i]]->SetTrackAValue(trackA->GetValue(keys[i]));
    }
  }
  if ( trackB ) {
    for (i = 0; i < keysSize; i++) {
      elementLines[keys[i]]->SetTrackBValue(trackB->GetValue(keys[i]));
    }
  }
  
  for ( i = 0 ; i < keysSize ; i ++) {
    elementLines[keys[i]]->Compare();
  }
}

/*****************************************************************************!
 * Function : SlotNextElement
 *****************************************************************************/
void
ControlDisplayForm::SlotNextElement
(int InMajorMinorFlags)
{
  ControlSignalPair*                    pair;
  if ( currentControlIndex + 1 >= controlInformation->GetPairCount() ) {
    return;
  }

  if ( InMajorMinorFlags == 0 ) {
    currentControlIndex++;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToNextMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToNextMinorSignal();
  } else if ( (InMajorMinorFlags & NAVIGATION_ONLY3_FLAG) || (InMajorMinorFlags & NAVIGATION_ONLY2_FLAG) ) {
    SkipToNextMissingSignal(InMajorMinorFlags);
  } else {
    SkipToNextAnySignal();
  }
  pair = controlInformation->GetPairByIndex(currentControlIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentControlIndex(currentControlIndex + 1);
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
ControlDisplayForm::SlotPreviousElement
(int InMajorMinorFlags)
{
  ControlSignalPair*                  pair;
  if ( currentControlIndex == 0 ) {
    return;
  }
  if ( InMajorMinorFlags == 0 ) {
    currentControlIndex--;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToPrevMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToPrevMinorSignal();
  } else if ( (InMajorMinorFlags & NAVIGATION_ONLY3_FLAG) || (InMajorMinorFlags & NAVIGATION_ONLY2_FLAG) ) {
    SkipToPrevMissingSignal(InMajorMinorFlags);
  } else {
    SkipToPrevAnySignal();
  }
  pair = controlInformation->GetPairByIndex(currentControlIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentControlIndex(currentControlIndex + 1);
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
ControlDisplayForm::SlotFirstElement(void)
{
  ControlSignalPair*                  pair;
  currentControlIndex = 0;
  pair = controlInformation->GetPairByIndex(currentControlIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentControlIndex(currentControlIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
ControlDisplayForm::SlotLastElement(void)
{
  ControlSignalPair*                  pair;
  currentControlIndex = controlInformation->GetPairCount() - 1;
  pair = controlInformation->GetPairByIndex(currentControlIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentControlIndex(currentControlIndex + 1);  
}

/*****************************************************************************!
 * Function : PairContainsMajorAlarm
 *****************************************************************************/
bool
ControlDisplayForm::PairContainsMajorAlarm
(ControlSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Major);
}

/*****************************************************************************!
 * Function : PairContainsMinorAlarm
 *****************************************************************************/
bool
ControlDisplayForm::PairContainsMinorAlarm
(ControlSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Minor);
}

/*****************************************************************************!
 * Function : PairContainsAlarm
 *****************************************************************************/
bool
ControlDisplayForm::PairContainsAlarm
(ControlSignalPair* InPair, ElementDisplayLine::DifferLevel InDifferType)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUControlSignal::Tags ) {
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
ControlDisplayForm::PairContainsAnyAlarm
(ControlSignalPair* InPair)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUControlSignal::Tags ) {
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
ControlDisplayForm::SkipToPrevMajorSignal
()
{
  int                                   n;
  ControlSignalPair*                      pair;

  currentControlIndex--;
  for ( n = currentControlIndex ; n > 0 ; n-- ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevMinorSignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToPrevMinorSignal
()
{
  int                                   n;
  ControlSignalPair*                      pair;

  currentControlIndex--;
  for ( n = currentControlIndex ; n > 0 ; n-- ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevAnySignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToPrevAnySignal
()
{
  int                                   n;
  ControlSignalPair*                      pair;

  currentControlIndex--;
  for ( n = currentControlIndex ; n > 0 ; n-- ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMajorSignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToNextMajorSignal
()
{
  int                                   n;
  int                                   m;
  ControlSignalPair*                      pair;

  currentControlIndex++;
  m = controlInformation->GetPairCount();
  for ( n = currentControlIndex ; n + 1 < m ; n++ ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMinorSignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToNextMinorSignal
()
{
  int                                   n;
  int                                   m;
  ControlSignalPair*                      pair;

  currentControlIndex++;
  m = controlInformation->GetPairCount();
  for ( n = currentControlIndex ; n + 1 < m ; n++ ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextAnySignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToNextAnySignal
()
{
  int                                   n;
  int                                   m;
  ControlSignalPair*                      pair;

  currentControlIndex++;
  m = controlInformation->GetPairCount();
  for ( n = currentControlIndex ; n + 1 < m ; n++ ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMissingSignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToNextMissingSignal
(int InMissingTracks)
{
  int                                   n;
  int                                   m;
  ControlSignalPair*                    pair;

  currentControlIndex++;
  m = controlInformation->GetPairCount();
  for ( n = currentControlIndex ; n + 1 < m ; n++ ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( InMissingTracks == NAVIGATION_ONLY3_FLAG ) {
      if ( pair->GetTrackA() == NULL ) {
        currentControlIndex = n;
        return;
      }
      continue;
    }
    if ( InMissingTracks == NAVIGATION_ONLY2_FLAG ) {
      if ( pair->GetTrackB() == NULL ) {
        currentControlIndex = n;
        return;
      }
      continue;
    }
    if ( pair->GetTrackA() == NULL || pair->GetTrackB() == NULL ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;  
}

/*****************************************************************************!
 * Function : SkipToPrevMissingSignal
 *****************************************************************************/
void
ControlDisplayForm::SkipToPrevMissingSignal
(int InMissingTracks)
{
  int                                   n;
  ControlSignalPair*                    pair;

  currentControlIndex--;
  for ( n = currentControlIndex ; n > 0 ; n-- ) {
    pair = controlInformation->GetPairByIndex(n);
    if ( InMissingTracks == NAVIGATION_ONLY3_FLAG ) {
      if ( pair->GetTrackA() == NULL ) {
        currentControlIndex = n;
        return;
      }
      continue;
    }
    if ( InMissingTracks == NAVIGATION_ONLY2_FLAG ) {
      if ( pair->GetTrackB() == NULL ) {
        currentControlIndex = n;
        return;
      }
      continue;
    }
    if ( pair->GetTrackA() == NULL || pair->GetTrackB() == NULL ) {
      currentControlIndex = n;
      return;
    }
  }
  currentControlIndex = n;
}

