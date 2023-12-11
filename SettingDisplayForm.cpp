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

  currentEquipIndex = 0;
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
    i->resize(width, ELEMENT_DISPLAY_LINE_HEIGHT);
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
 * Function : SlotNextElement
 *****************************************************************************/
void
SettingDisplayForm::SlotNextElement
(int)
{
  SettingSignalPair*                  pair;
  if ( currentEquipIndex + 1 >= settingInformation->GetPairCount() ) {
    return;
  }

  currentEquipIndex++;
  pair = settingInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentSettingIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
SettingDisplayForm::SlotPreviousElement
(int)
{
  SettingSignalPair*                  pair;
  if ( currentEquipIndex == 0 ) {
    return;
  }
  currentEquipIndex--;
  pair = settingInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
    emit SignalSetCurrentSettingIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
SettingDisplayForm::SetTrackInformation
(SettingSignalPair* InPair)
{
  
  int                                   i;
  NCUSettingSignal*                     track2;
  NCUSettingSignal*                     track3;

  SettingIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines[i++]->SetTrack2Value(track2->SETName);
    elementLines[i++]->SetTrack2Value(track2->Unit);
    elementLines[i++]->SetTrack2Value(track2->SIndx);
    elementLines[i++]->SetTrack2Value(track2->SChan);
    elementLines[i++]->SetTrack2Value(track2->ValType);
    elementLines[i++]->SetTrack2Value(track2->Def);
    elementLines[i++]->SetTrack2Value(track2->Range);
    elementLines[i++]->SetTrack2Value(track2->DisplayAttr);
    elementLines[i++]->SetTrack2Value(track2->SetAttr);
    elementLines[i++]->SetTrack2Value(track2->SetExpRPN);
    elementLines[i++]->SetTrack2Value(track2->SetExpFull);
    elementLines[i++]->SetTrack2Value(track2->Auth);
    elementLines[i++]->SetTrack2Value(track2->DisplayID);
    elementLines[i++]->SetTrack2Value(track2->DispFmt);
    elementLines[i++]->SetTrack2Value(track2->ChID);
    elementLines[i++]->SetTrack2Value(track2->Step);
    elementLines[i++]->SetTrack2Value(track2->CExpRPN);
    elementLines[i++]->SetTrack2Value(track2->CExpFull);
    elementLines[i++]->SetTrack2Value(track2->Persist);
    elementLines[i++]->SetTrack2Value(track2->DispExpRPN);
    elementLines[i++]->SetTrack2Value(track2->DispExpFull);
    elementLines[i++]->SetTrack2Value(track2->States);
    elementLines[i++]->SetTrack2Value(track2->OnCtrl);
  }

  if ( track3 ) {
    i = 0;
    elementLines[i++]->SetTrack3Value(track3->SETName);
    elementLines[i++]->SetTrack3Value(track3->Unit);
    elementLines[i++]->SetTrack3Value(track3->SIndx);
    elementLines[i++]->SetTrack3Value(track3->SChan);
    elementLines[i++]->SetTrack3Value(track3->ValType);
    elementLines[i++]->SetTrack3Value(track3->Def);
    elementLines[i++]->SetTrack3Value(track3->Range);
    elementLines[i++]->SetTrack3Value(track3->DisplayAttr);
    elementLines[i++]->SetTrack3Value(track3->SetAttr);
    elementLines[i++]->SetTrack3Value(track3->SetExpRPN);
    elementLines[i++]->SetTrack3Value(track3->SetExpFull);
    elementLines[i++]->SetTrack3Value(track3->Auth);
    elementLines[i++]->SetTrack3Value(track3->DisplayID);
    elementLines[i++]->SetTrack3Value(track3->DispFmt);
    elementLines[i++]->SetTrack3Value(track3->ChID);
    elementLines[i++]->SetTrack3Value(track3->Step);
    elementLines[i++]->SetTrack3Value(track3->CExpRPN);
    elementLines[i++]->SetTrack3Value(track3->CExpFull);
    elementLines[i++]->SetTrack3Value(track3->Persist);
    elementLines[i++]->SetTrack3Value(track3->DispExpRPN);
    elementLines[i++]->SetTrack3Value(track3->DispExpFull);
    elementLines[i++]->SetTrack3Value(track3->States);
    elementLines[i++]->SetTrack3Value(track3->OnCtrl);
  }

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Compare();
  }
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
SettingDisplayForm::SlotFirstElement
(void)
{
  SettingSignalPair*                  pair;
  currentEquipIndex = 0;
  pair = settingInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSettingIndex(currentEquipIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
SettingDisplayForm::SlotLastElement
(void)
{
  SettingSignalPair*                  pair;
  currentEquipIndex = settingInformation->GetPairCount() - 1;
  pair = settingInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentSettingIndex(currentEquipIndex + 1);  
}

