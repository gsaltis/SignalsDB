/*****************************************************************************
 * FILE NAME    : SampleDisplayForm.cpp
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
#include "SampleDisplayForm.h"
#include "ElementDisplayLine.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : SampleDisplayForm
 *****************************************************************************/
SampleDisplayForm::SampleDisplayForm
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
 * Function : ~SampleDisplayForm
 *****************************************************************************/
SampleDisplayForm::~SampleDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SampleDisplayForm::initialize()
{
  SampleSignalPair*                  pair;

  currentSampleIndex = 0;
  sampleInformation = MainConfig::sampleInformation;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  pair = sampleInformation->GetPairByIndex(0);
  SetTrackInformation(pair);
  navigationWindow->SlotSetCurrentSignalIndex(1);
  navigationWindow->SlotSetSignalCount(sampleInformation->GetPairCount());
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SampleDisplayForm::CreateSubWindows()
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
  label->setText(QString("Sample ID : "));
  label->setAlignment(Qt::AlignRight);

  SampleIDLabel = new QLabel(this);
  SampleIDLabel->move(x1 + 230, y);
  SampleIDLabel->resize(80, labelHeight);
  SampleIDLabel->setAlignment(Qt::AlignLeft);
  SampleIDLabel->setFont(valueFont);

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
  AddElementLines("Samples", y);

  navigationWindow = new NavigationWindow();
  navigationWindow->move(10, y);
  navigationWindow->resize(labelWidth + 20, NAVIGATION_WINDOW_HEIGHT);
  navigationWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SampleDisplayForm::InitializeSubWindows()
{
  navigationWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SampleDisplayForm::resizeEvent
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
  
  Track3Label->move(x4, Track3Label->pos().y());
  
  for ( auto i : elementLines ) {
    i->resize(width, ELEMENT_DISPLAY_LINE_HEIGHT);
  }
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
SampleDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalFirstElement,
          this,
          SampleDisplayForm::SlotFirstElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalLastElement,
          this,
          SampleDisplayForm::SlotLastElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalNextElement,
          this,
          SampleDisplayForm::SlotNextElement);

  connect(navigationWindow,
          NavigationWindow::SignalPreviousElement,
          this,
          SampleDisplayForm::SlotPreviousElement);

  connect(this,
          SampleDisplayForm::SignalSetCurrentSampleIndex,
          navigationWindow,
          NavigationWindow::SlotSetCurrentSignalIndex);
}

/*****************************************************************************!
 * Function : SlotNextElement
 *****************************************************************************/
void
SampleDisplayForm::SlotNextElement
(int InMajorMinorFlags)
{
  SampleSignalPair*                    pair;
  if ( currentSampleIndex + 1 >= sampleInformation->GetPairCount() ) {
    return;
  }

  if ( InMajorMinorFlags == 0 ) {
    currentSampleIndex++;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToNextMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToNextMinorSignal();
  } else {
    SkipToNextAnySignal();
  }
  pair = sampleInformation->GetPairByIndex(currentSampleIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentSampleIndex(currentSampleIndex + 1);
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
SampleDisplayForm::SlotPreviousElement
(int InMajorMinorFlags)
{
  SampleSignalPair*                  pair;
  if ( currentSampleIndex == 0 ) {
    return;
  }
  if ( InMajorMinorFlags == 0 ) {
    currentSampleIndex--;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToPrevMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToPrevMinorSignal();
  } else {
    SkipToPrevAnySignal();
  }
  pair = sampleInformation->GetPairByIndex(currentSampleIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSampleIndex(currentSampleIndex + 1);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
SampleDisplayForm::SetTrackInformation
(SampleSignalPair* InPair)
{
  int                                   keysSize;
  QStringList                           keys;
  
  int                                   i;
  NCUSampleSignal*                      track2;
  NCUSampleSignal*                      track3;

  SampleIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  keys = elementLines.keys();
  keysSize = keys.size();
  for ( i = 0 ; i < keysSize ; i++ ) {
    elementLines[keys[i]]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines["SAMPLEName"]->SetTrack2Value(track2->GetValue("SAMPLEName"));
    elementLines["Unit"]->SetTrack2Value(track2->GetValue("Unit"));
    elementLines["SIndx"]->SetTrack2Value(track2->GetValue("SIndx"));
    elementLines["SChan"]->SetTrack2Value(track2->GetValue("SChan"));
    elementLines["ValType"]->SetTrack2Value(track2->GetValue("ValType"));
    elementLines["StorThreshold"]->SetTrack2Value(track2->GetValue("StorThreshold"));
    elementLines["StorInt"]->SetTrack2Value(track2->GetValue("StorInt"));
    elementLines["EvalExpRPN"]->SetTrack2Value(track2->GetValue("EvalExpRPN"));
    elementLines["EvalExpFull"]->SetTrack2Value(track2->GetValue("EvalExpFull"));
    elementLines["Range"]->SetTrack2Value(track2->GetValue("Range"));
    elementLines["DisplayAttr"]->SetTrack2Value(track2->GetValue("DisplayAttr"));
    elementLines["DisplayLvl"]->SetTrack2Value(track2->GetValue("DisplayLvl"));
    elementLines["DisplayID"]->SetTrack2Value(track2->GetValue("DisplayID"));
    elementLines["DispFmt"]->SetTrack2Value(track2->GetValue("DispFmt"));
    elementLines["DispExpRPN"]->SetTrack2Value(track2->GetValue("DispExpRPN"));
    elementLines["DispExpFull"]->SetTrack2Value(track2->GetValue("DispExpFull"));
    elementLines["Enums"]->SetTrack2Value(track2->GetValue("Enums"));
  }

  if ( track3 ) {
    i = 0;
    elementLines["SAMPLEName"]->SetTrack3Value(track3->GetValue("SAMPLEName"));
    elementLines["Unit"]->SetTrack3Value(track3->GetValue("Unit"));
    elementLines["SIndx"]->SetTrack3Value(track3->GetValue("SIndx"));
    elementLines["SChan"]->SetTrack3Value(track3->GetValue("SChan"));
    elementLines["ValType"]->SetTrack3Value(track3->GetValue("ValType"));
    elementLines["StorThreshold"]->SetTrack3Value(track3->GetValue("StorThreshold"));
    elementLines["StorInt"]->SetTrack3Value(track3->GetValue("StorInt"));
    elementLines["EvalExpRPN"]->SetTrack3Value(track3->GetValue("EvalExpRPN"));
    elementLines["EvalExpFull"]->SetTrack3Value(track3->GetValue("EvalExpFull"));
    elementLines["Range"]->SetTrack3Value(track3->GetValue("Range"));
    elementLines["DisplayAttr"]->SetTrack3Value(track3->GetValue("DisplayAttr"));
    elementLines["DisplayLvl"]->SetTrack3Value(track3->GetValue("DisplayLvl"));
    elementLines["DisplayID"]->SetTrack3Value(track3->GetValue("DisplayID"));
    elementLines["DispFmt"]->SetTrack3Value(track3->GetValue("DispFmt"));
    elementLines["DispExpRPN"]->SetTrack3Value(track3->GetValue("DispExpRPN"));
    elementLines["DispExpFull"]->SetTrack3Value(track3->GetValue("DispExpFull"));
    elementLines["Enums"]->SetTrack3Value(track3->GetValue("Enums"));
  }
  
  for ( i = 0 ; i < keysSize ; i++ ) {
    elementLines[keys[i]]->Compare();
  }
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
SampleDisplayForm::SlotFirstElement
(void)
{
  SampleSignalPair*                  pair;
  currentSampleIndex = 0;
  pair = sampleInformation->GetPairByIndex(currentSampleIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSampleIndex(currentSampleIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
SampleDisplayForm::SlotLastElement
(void)
{
  SampleSignalPair*                  pair;
  currentSampleIndex = sampleInformation->GetPairCount() - 1;
  pair = sampleInformation->GetPairByIndex(currentSampleIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSampleIndex(currentSampleIndex + 1);  
}

/*****************************************************************************!
 * Function : PairContainsMajorAlarm
 *****************************************************************************/
bool
SampleDisplayForm::PairContainsMajorAlarm
(SampleSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Major);
}

/*****************************************************************************!
 * Function : PairContainsMinorAlarm
 *****************************************************************************/
bool
SampleDisplayForm::PairContainsMinorAlarm
(SampleSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Minor);
}

/*****************************************************************************!
 * Function : PairContainsAlarm
 *****************************************************************************/
bool
SampleDisplayForm::PairContainsAlarm
(SampleSignalPair* InPair, ElementDisplayLine::DifferLevel InDifferType)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUSampleSignal::Tags ) {
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
SampleDisplayForm::PairContainsAnyAlarm
(SampleSignalPair* InPair)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUSampleSignal::Tags ) {
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
SampleDisplayForm::SkipToPrevMajorSignal(void)
{
  int                                   n;
  SampleSignalPair*                      pair;

  currentSampleIndex--;
  for ( n = currentSampleIndex ; n > 0 ; n-- ) {
    pair = sampleInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentSampleIndex = n;
      return;
    }
  }
  currentSampleIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevMinorSignal
 *****************************************************************************/
void
SampleDisplayForm::SkipToPrevMinorSignal(void)
{
  int                                   n;
  SampleSignalPair*                      pair;

  currentSampleIndex--;
  for ( n = currentSampleIndex ; n > 0 ; n-- ) {
    pair = sampleInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentSampleIndex = n;
      return;
    }
  }
  currentSampleIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevAnySignal
 *****************************************************************************/
void
SampleDisplayForm::SkipToPrevAnySignal(void)
{
  int                                   n;
  SampleSignalPair*                      pair;

  currentSampleIndex--;
  for ( n = currentSampleIndex ; n > 0 ; n-- ) {
    pair = sampleInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentSampleIndex = n;
      return;
    }
  }
  currentSampleIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMajorSignal
 *****************************************************************************/
void
SampleDisplayForm::SkipToNextMajorSignal(void)
{
  int                                   n;
  int                                   m;
  SampleSignalPair*                      pair;

  currentSampleIndex++;
  m = sampleInformation->GetPairCount();
  for ( n = currentSampleIndex ; n + 1 < m ; n++ ) {
    pair = sampleInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentSampleIndex = n;
      return;
    }
  }
  currentSampleIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMinorSignal
 *****************************************************************************/
void
SampleDisplayForm::SkipToNextMinorSignal(void)
{
  int                                   n;
  int                                   m;
  SampleSignalPair*                      pair;

  currentSampleIndex++;
  m = sampleInformation->GetPairCount();
  for ( n = currentSampleIndex ; n + 1 < m ; n++ ) {
    pair = sampleInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentSampleIndex = n;
      return;
    }
  }
  currentSampleIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextAnySignal
 *****************************************************************************/
void
SampleDisplayForm::SkipToNextAnySignal(void)
{
  int                                   n;
  int                                   m;
  SampleSignalPair*                      pair;

  currentSampleIndex++;
  m = sampleInformation->GetPairCount();
  for ( n = currentSampleIndex ; n + 1 < m ; n++ ) {
    pair = sampleInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentSampleIndex = n;
      return;
    }
  }
  currentSampleIndex = n;
}
