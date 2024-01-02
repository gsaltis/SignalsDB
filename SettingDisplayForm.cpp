/*****************************************************************************
 * FILE NAME    : SettingDisplayForm.cpp
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
#include "SettingDisplayForm.h"
#include "ElementDisplayLine.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : SettingDisplayForm
 *****************************************************************************/
SettingDisplayForm::SettingDisplayForm
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
 * Function : ~SettingDisplayForm
 *****************************************************************************/
SettingDisplayForm::~SettingDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SettingDisplayForm::initialize()
{
  SettingSignalPair*                  pair;

  currentSettingIndex = 0;
  settingInformation = MainConfig::settingInformation;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  pair = settingInformation->GetPairByIndex(0);
  SetTrackInformation(pair);
  navigationWindow->SlotSetCurrentSignalIndex(1);
  navigationWindow->SlotSetSignalCount(settingInformation->GetPairCount());
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SettingDisplayForm::CreateSubWindows()
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
  label->setText(QString("Setting ID : "));
  label->setAlignment(Qt::AlignRight);

  SettingIDLabel = new QLabel(this);
  SettingIDLabel->move(x1 + 230, y);
  SettingIDLabel->resize(80, labelHeight);
  SettingIDLabel->setAlignment(Qt::AlignLeft);
  SettingIDLabel->setFont(valueFont);

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
  AddElementLines("Settings", y);
  
  //!
  navigationWindow = new NavigationWindow();
  navigationWindow->move(10, y);
  navigationWindow->resize(labelWidth + 20, NAVIGATION_WINDOW_HEIGHT);
  navigationWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SettingDisplayForm::InitializeSubWindows()
{
  navigationWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SettingDisplayForm::resizeEvent
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
SettingDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalFirstElement,
          this,
          SettingDisplayForm::SlotFirstElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalLastElement,
          this,
          SettingDisplayForm::SlotLastElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalNextElement,
          this,
          SettingDisplayForm::SlotNextElement);

  connect(navigationWindow,
          NavigationWindow::SignalPreviousElement,
          this,
          SettingDisplayForm::SlotPreviousElement);

  connect(this,
          SettingDisplayForm::SignalSetCurrentSettingIndex,
          navigationWindow,
          NavigationWindow::SlotSetCurrentSignalIndex);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
SettingDisplayForm::SetTrackInformation
(SettingSignalPair* InPair)
{
  int                                   keysSize;
  QStringList                           keys;
  
  int                                   i;
  NCUSettingSignal*                     track2;
  NCUSettingSignal*                     track3;

  SettingIDLabel->setText(QString("%1").arg(InPair->GetID()));
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
    elementLines["SETName"]->SetTrack2Value(track2->GetValue("SETName"));
    elementLines["Unit"]->SetTrack2Value(track2->GetValue("Unit"));
    elementLines["SIndx"]->SetTrack2Value(track2->GetValue("SIndx"));
    elementLines["SChan"]->SetTrack2Value(track2->GetValue("SChan"));
    elementLines["ValType"]->SetTrack2Value(track2->GetValue("ValType"));
    elementLines["Def"]->SetTrack2Value(track2->GetValue("Def"));
    elementLines["Range"]->SetTrack2Value(track2->GetValue("Range"));
    elementLines["DisplayAttr"]->SetTrack2Value(track2->GetValue("DisplayAttr"));
    elementLines["SetAttr"]->SetTrack2Value(track2->GetValue("SetAttr"));
    elementLines["SetExpRPN"]->SetTrack2Value(track2->GetValue("SetExpRPN"));
    elementLines["SetExpFull"]->SetTrack2Value(track2->GetValue("SetExpFull"));
    elementLines["Auth"]->SetTrack2Value(track2->GetValue("Auth"));
    elementLines["DisplayID"]->SetTrack2Value(track2->GetValue("DisplayID"));
    elementLines["DispFmt"]->SetTrack2Value(track2->GetValue("DispFmt"));
    elementLines["ChID"]->SetTrack2Value(track2->GetValue("ChID"));
    elementLines["Step"]->SetTrack2Value(track2->GetValue("Step"));
    elementLines["CExpRPN"]->SetTrack2Value(track2->GetValue("CExpRPN"));
    elementLines["CExpFull"]->SetTrack2Value(track2->GetValue("CExpFull"));
    elementLines["Persist"]->SetTrack2Value(track2->GetValue("Persist"));
    elementLines["DispExpRPN"]->SetTrack2Value(track2->GetValue("DispExpRPN"));
    elementLines["DispExpFull"]->SetTrack2Value(track2->GetValue("DispExpFull"));
    elementLines["States"]->SetTrack2Value(track2->GetValue("States"));
    elementLines["OnCtrl"]->SetTrack2Value(track2->GetValue("OnCtrl"));
  }

  if ( track3 ) {
    i = 0;
    elementLines["SETName"]->SetTrack3Value(track3->GetValue("SETName"));
    elementLines["Unit"]->SetTrack3Value(track3->GetValue("Unit"));
    elementLines["SIndx"]->SetTrack3Value(track3->GetValue("SIndx"));
    elementLines["SChan"]->SetTrack3Value(track3->GetValue("SChan"));
    elementLines["ValType"]->SetTrack3Value(track3->GetValue("ValType"));
    elementLines["Def"]->SetTrack3Value(track3->GetValue("Def"));
    elementLines["Range"]->SetTrack3Value(track3->GetValue("Range"));
    elementLines["DisplayAttr"]->SetTrack3Value(track3->GetValue("DisplayAttr"));
    elementLines["SetAttr"]->SetTrack3Value(track3->GetValue("SetAttr"));
    elementLines["SetExpRPN"]->SetTrack3Value(track3->GetValue("SetExpRPN"));
    elementLines["SetExpFull"]->SetTrack3Value(track3->GetValue("SetExpFull"));
    elementLines["Auth"]->SetTrack3Value(track3->GetValue("Auth"));
    elementLines["DisplayID"]->SetTrack3Value(track3->GetValue("DisplayID"));
    elementLines["DispFmt"]->SetTrack3Value(track3->GetValue("DispFmt"));
    elementLines["ChID"]->SetTrack3Value(track3->GetValue("ChID"));
    elementLines["Step"]->SetTrack3Value(track3->GetValue("Step"));
    elementLines["CExpRPN"]->SetTrack3Value(track3->GetValue("CExpRPN"));
    elementLines["CExpFull"]->SetTrack3Value(track3->GetValue("CExpFull"));
    elementLines["Persist"]->SetTrack3Value(track3->GetValue("Persist"));
    elementLines["DispExpRPN"]->SetTrack3Value(track3->GetValue("DispExpRPN"));
    elementLines["DispExpFull"]->SetTrack3Value(track3->GetValue("DispExpFull"));
    elementLines["States"]->SetTrack3Value(track3->GetValue("States"));
    elementLines["OnCtrl"]->SetTrack3Value(track3->GetValue("OnCtrl"));
  }

  for ( i = 0 ; i < keysSize ; i++ ) {
    elementLines[keys[i]]->Compare();
  }
}

/*****************************************************************************!
 * Function : SlotNextElement
 *****************************************************************************/
void
SettingDisplayForm::SlotNextElement
(int InMajorMinorFlags)
{
  SettingSignalPair*                    pair;
  if ( currentSettingIndex + 1 >= settingInformation->GetPairCount() ) {
    return;
  }

  if ( InMajorMinorFlags == 0 ) {
    currentSettingIndex++;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToNextMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToNextMinorSignal();
  } else if ( (InMajorMinorFlags & NAVIGATION_ONLY3_FLAG) || (InMajorMinorFlags & NAVIGATION_ONLY2_FLAG) ) {
    SkipToNextMissingSignal(InMajorMinorFlags);
  } else {
    SkipToNextAnySignal();
  }
  pair = settingInformation->GetPairByIndex(currentSettingIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentSettingIndex(currentSettingIndex + 1);
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
SettingDisplayForm::SlotPreviousElement
(int InMajorMinorFlags)
{
  SettingSignalPair*                  pair;
  if ( currentSettingIndex == 0 ) {
    return;
  }
  if ( InMajorMinorFlags == 0 ) {
    currentSettingIndex--;
  } else if ( InMajorMinorFlags == NAVIGATION_MAJOR_FLAG ) {
    SkipToPrevMajorSignal();
  } else if ( InMajorMinorFlags == NAVIGATION_MINOR_FLAG ) {
    SkipToPrevMinorSignal();
  } else if ( (InMajorMinorFlags & NAVIGATION_ONLY3_FLAG) || (InMajorMinorFlags & NAVIGATION_ONLY2_FLAG) ) {
    SkipToPrevMissingSignal(InMajorMinorFlags);
  } else {
    SkipToPrevAnySignal();
  }
  pair = settingInformation->GetPairByIndex(currentSettingIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSettingIndex(currentSettingIndex + 1);
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
SettingDisplayForm::SlotFirstElement
(void)
{
  SettingSignalPair*                  pair;
  currentSettingIndex = 0;
  pair = settingInformation->GetPairByIndex(currentSettingIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSettingIndex(currentSettingIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
SettingDisplayForm::SlotLastElement
(void)
{
  SettingSignalPair*                  pair;
  currentSettingIndex = settingInformation->GetPairCount() - 1;
  pair = settingInformation->GetPairByIndex(currentSettingIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSettingIndex(currentSettingIndex + 1);  
}

/*****************************************************************************!
 * Function : PairContainsMajorAlarm
 *****************************************************************************/
bool
SettingDisplayForm::PairContainsMajorAlarm
(SettingSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Major);
}

/*****************************************************************************!
 * Function : PairContainsMinorAlarm
 *****************************************************************************/
bool
SettingDisplayForm::PairContainsMinorAlarm
(SettingSignalPair* InPair)
{
  return PairContainsAlarm(InPair, ElementDisplayLine::Minor);
}

/*****************************************************************************!
 * Function : PairContainsAlarm
 *****************************************************************************/
bool
SettingDisplayForm::PairContainsAlarm
(SettingSignalPair* InPair, ElementDisplayLine::DifferLevel InDifferType)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUSettingSignal::Tags ) {
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
SettingDisplayForm::PairContainsAnyAlarm
(SettingSignalPair* InPair)
{
  ElementDisplayLine*                   displayLine;
  ElementDisplayLine::DifferLevel       differType;

  for ( auto tag : NCUSettingSignal::Tags ) {
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
SettingDisplayForm::SkipToPrevMajorSignal
()
{
  int                                   n;
  SettingSignalPair*                      pair;

  currentSettingIndex--;
  for ( n = currentSettingIndex ; n > 0 ; n-- ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevMinorSignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToPrevMinorSignal
()
{
  int                                   n;
  SettingSignalPair*                      pair;

  currentSettingIndex--;
  for ( n = currentSettingIndex ; n > 0 ; n-- ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

/*****************************************************************************!
 * Function : SkipToPrevAnySignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToPrevAnySignal
()
{
  int                                   n;
  SettingSignalPair*                      pair;

  currentSettingIndex--;
  for ( n = currentSettingIndex ; n > 0 ; n-- ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMajorSignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToNextMajorSignal
()
{
  int                                   n;
  int                                   m;
  SettingSignalPair*                      pair;

  currentSettingIndex++;
  m = settingInformation->GetPairCount();
  for ( n = currentSettingIndex ; n + 1 < m ; n++ ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( PairContainsMajorAlarm(pair) ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMinorSignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToNextMinorSignal
()
{
  int                                   n;
  int                                   m;
  SettingSignalPair*                      pair;

  currentSettingIndex++;
  m = settingInformation->GetPairCount();
  for ( n = currentSettingIndex ; n + 1 < m ; n++ ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( PairContainsMinorAlarm(pair) ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextAnySignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToNextAnySignal
()
{
  int                                   n;
  int                                   m;
  SettingSignalPair*                      pair;

  currentSettingIndex++;
  m = settingInformation->GetPairCount();
  for ( n = currentSettingIndex ; n + 1 < m ; n++ ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( PairContainsAnyAlarm(pair) ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

/*****************************************************************************!
 * Function : SkipToNextMissingSignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToNextMissingSignal
(int InMissingTracks)
{
  int                                   n;
  int                                   m;
  SettingSignalPair*                    pair;

  currentSettingIndex++;
  m = settingInformation->GetPairCount();
  for ( n = currentSettingIndex ; n + 1 < m ; n++ ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( InMissingTracks == NAVIGATION_ONLY3_FLAG ) {
      if ( pair->GetTrack2() == NULL ) {
        currentSettingIndex = n;
        return;
      }
      continue;
    }
    if ( InMissingTracks == NAVIGATION_ONLY2_FLAG ) {
      if ( pair->GetTrack3() == NULL ) {
        currentSettingIndex = n;
        return;
      }
      continue;
    }
    if ( pair->GetTrack2() == NULL || pair->GetTrack3() == NULL ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;  
}

/*****************************************************************************!
 * Function : SkipToPrevMissingSignal
 *****************************************************************************/
void
SettingDisplayForm::SkipToPrevMissingSignal
(int InMissingTracks)
{
  int                                   n;
  SettingSignalPair*                    pair;

  currentSettingIndex--;
  for ( n = currentSettingIndex ; n > 0 ; n-- ) {
    pair = settingInformation->GetPairByIndex(n);
    if ( InMissingTracks == NAVIGATION_ONLY3_FLAG ) {
      if ( pair->GetTrack2() == NULL ) {
        currentSettingIndex = n;
        return;
      }
      continue;
    }
    if ( InMissingTracks == NAVIGATION_ONLY2_FLAG ) {
      if ( pair->GetTrack3() == NULL ) {
        currentSettingIndex = n;
        return;
      }
      continue;
    }
    if ( pair->GetTrack2() == NULL || pair->GetTrack3() == NULL ) {
      currentSettingIndex = n;
      return;
    }
  }
  currentSettingIndex = n;
}

