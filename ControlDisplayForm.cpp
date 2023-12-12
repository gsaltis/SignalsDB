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
  label->setText(QString("Control ID : "));
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
  
  Track3Label->move(x4, Track3Label->pos().y());

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
  NCUControlSignal*                     track2;
  NCUControlSignal*                     track3;

  ControlIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  keys = elementLines.keys();
  keysSize  = keys.size();
  for ( i = 0 ; i < keysSize ; i ++) {
    elementLines[keys[i]]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines["CTRLName"]->SetTrack2Value(track2->GetValue("CTRLName"));
    elementLines["Unit"]->SetTrack2Value(track2->GetValue("Unit"));
    elementLines["SIndx"]->SetTrack2Value(track2->GetValue("SIndx"));
    elementLines["SChan"]->SetTrack2Value(track2->GetValue("SChan"));
    elementLines["ValType"]->SetTrack2Value(track2->GetValue("ValType"));
    elementLines["Defaults"]->SetTrack2Value(track2->GetValue("Defaults"));
    elementLines["Range"]->SetTrack2Value(track2->GetValue("Range"));
    elementLines["DisplayAttr"]->SetTrack2Value(track2->GetValue("DisplayAttr"));
    elementLines["CtrlAttr"]->SetTrack2Value(track2->GetValue("CtrlAttr"));
    elementLines["Threshold"]->SetTrack2Value(track2->GetValue("Threshold"));
    elementLines["CableExpRPN"]->SetTrack2Value(track2->GetValue("CableExpRPN"));
    elementLines["CableExpFull"]->SetTrack2Value(track2->GetValue("CableExpFull"));
    elementLines["Auth"]->SetTrack2Value(track2->GetValue("Auth"));
    elementLines["DisplayID"]->SetTrack2Value(track2->GetValue("DisplayID"));
    elementLines["DispFmt"]->SetTrack2Value(track2->GetValue("DispFmt"));
    elementLines["ChID"]->SetTrack2Value(track2->GetValue("ChID"));
    elementLines["CStep"]->SetTrack2Value(track2->GetValue("CStep"));
    elementLines["CParam"]->SetTrack2Value(track2->GetValue("CParam"));
    elementLines["CexpRPN"]->SetTrack2Value(track2->GetValue("CexpRPN"));
    elementLines["CexpFullDispExp"]->SetTrack2Value(track2->GetValue("CexpFullDispExp"));
    elementLines["States"]->SetTrack2Value(track2->GetValue("States"));
    elementLines["CAction"]->SetTrack2Value(track2->GetValue("CAction"));
  }

  if ( track3 ) {
    i = 0;
    elementLines["CTRLName"]->SetTrack3Value(track3->GetValue("CTRLName"));
    elementLines["Unit"]->SetTrack3Value(track3->GetValue("Unit"));
    elementLines["SIndx"]->SetTrack3Value(track3->GetValue("SIndx"));
    elementLines["SChan"]->SetTrack3Value(track3->GetValue("SChan"));
    elementLines["ValType"]->SetTrack3Value(track3->GetValue("ValType"));
    elementLines["Defaults"]->SetTrack3Value(track3->GetValue("Defaults"));
    elementLines["Range"]->SetTrack3Value(track3->GetValue("Range"));
    elementLines["DisplayAttr"]->SetTrack3Value(track3->GetValue("DisplayAttr"));
    elementLines["CtrlAttr"]->SetTrack3Value(track3->GetValue("CtrlAttr"));
    elementLines["Threshold"]->SetTrack3Value(track3->GetValue("Threshold"));
    elementLines["CableExpRPN"]->SetTrack3Value(track3->GetValue("CableExpRPN"));
    elementLines["CableExpFull"]->SetTrack3Value(track3->GetValue("CableExpFull"));
    elementLines["Auth"]->SetTrack3Value(track3->GetValue("Auth"));
    elementLines["DisplayID"]->SetTrack3Value(track3->GetValue("DisplayID"));
    elementLines["DispFmt"]->SetTrack3Value(track3->GetValue("DispFmt"));
    elementLines["ChID"]->SetTrack3Value(track3->GetValue("ChID"));
    elementLines["CStep"]->SetTrack3Value(track3->GetValue("CStep"));
    elementLines["CParam"]->SetTrack3Value(track3->GetValue("CParam"));
    elementLines["CexpRPN"]->SetTrack3Value(track3->GetValue("CexpRPN"));
    elementLines["CexpFullDispExp"]->SetTrack3Value(track3->GetValue("CexpFullDispExp"));
    elementLines["States"]->SetTrack3Value(track3->GetValue("States"));
    elementLines["CAction"]->SetTrack3Value(track3->GetValue("CAction"));
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
ControlDisplayForm::SkipToPrevMajorSignal(void)
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
ControlDisplayForm::SkipToPrevMinorSignal(void)
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
ControlDisplayForm::SkipToPrevAnySignal(void)
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
ControlDisplayForm::SkipToNextMajorSignal(void)
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
ControlDisplayForm::SkipToNextMinorSignal(void)
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
ControlDisplayForm::SkipToNextAnySignal(void)
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

