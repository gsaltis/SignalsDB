/*****************************************************************************
 * FILE NAME    : EquipmentDisplayForm.cpp
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
#include "EquipmentDisplayForm.h"
#include "ElementDisplayLine.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : EquipmentDisplayForm
 *****************************************************************************/
EquipmentDisplayForm::EquipmentDisplayForm
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
 * Function : ~EquipmentDisplayForm
 *****************************************************************************/
EquipmentDisplayForm::~EquipmentDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
EquipmentDisplayForm::initialize()
{
  EquipmentSignalPair*                  pair;

  currentEquipIndex = 0;
  equipmentInformation = MainConfig::equipmentInformation;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  pair = equipmentInformation->GetPairByIndex(0);
  SetTrackInformation(pair);
  navigationWindow->SlotSetCurrentSignalIndex(1);
  navigationWindow->SlotSetSignalCount(equipmentInformation->GetPairCount());
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
EquipmentDisplayForm::CreateSubWindows()
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
  y = 10;
  label = new QLabel();
  label->setParent(this);
  label->move(x1, y);
  label->resize(225, labelHeight);
  label->setFont(labelFont);
  label->setText(QString("Equipment ID : "));
  label->setAlignment(Qt::AlignRight);

  EquipmentIDLabel = new QLabel(this);
  EquipmentIDLabel->move(x1 + 230, y);
  EquipmentIDLabel->resize(80, labelHeight);
  EquipmentIDLabel->setAlignment(Qt::AlignLeft);
  EquipmentIDLabel->setFont(valueFont);

  //!
  y = 55;
  AddElementLines("Equipment", y);

  navigationWindow = new NavigationWindow();
  navigationWindow->move(10, y);
  navigationWindow->resize(labelWidth + 20, NAVIGATION_WINDOW_HEIGHT);
  navigationWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
EquipmentDisplayForm::InitializeSubWindows()
{
  navigationWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
EquipmentDisplayForm::resizeEvent
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
EquipmentDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalNextDifferElement,
          this,
          EquipmentDisplayForm::SlotNextDifferElement);
  connect(navigationWindow,
          NavigationWindow::SignalPrevDifferElement,
          this,
          EquipmentDisplayForm::SlotPrevDifferElement);
  connect(navigationWindow,
          NavigationWindow::SignalNextElement,
          this,
          EquipmentDisplayForm::SlotNextElement);
  connect(navigationWindow,
          NavigationWindow::SignalPreviousElement,
          this,
          EquipmentDisplayForm::SlotPreviousElement);
  connect(this,
          EquipmentDisplayForm::SignalSetCurrentEquipmentIndex,
          navigationWindow,
          NavigationWindow::SlotSetCurrentSignalIndex);
}

/*****************************************************************************!
 * Function : SlotNextElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotNextElement(void)
{
  EquipmentSignalPair*                  pair;
  if ( currentEquipIndex + 1 >= equipmentInformation->GetPairCount() ) {
    return;
  }

  currentEquipIndex++;
  pair = equipmentInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentEquipmentIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SlotNextDifferElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotNextDifferElement(void)
{
  int                                   i, n;
  EquipmentSignalPair*                  pair;
  
  n = equipmentInformation->GetPairCount();

  for ( i = currentEquipIndex + 1 ; i < n ; i++ ) {
    pair = equipmentInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentEquipmentIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPrevDifferElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotPrevDifferElement(void)
{
  int                                   i;
  EquipmentSignalPair*                  pair;
  
  for ( i = currentEquipIndex - 1; i >= 0 ; i-- ) {
    pair = equipmentInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentEquipmentIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotPreviousElement(void)
{
  EquipmentSignalPair*                  pair;
  if ( currentEquipIndex == 0 ) {
    return;
  }
  currentEquipIndex--;
  pair = equipmentInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
    emit SignalSetCurrentEquipmentIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
EquipmentDisplayForm::SetTrackInformation
(EquipmentSignalPair* InPair)
{
  int                                   i;
  NCUEquipment*                         track2;
  NCUEquipment*                         track3;

  EquipmentIDLabel->setText(QString("%1").arg(InPair->GetID()));

  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Clear();
  }

  if ( track2 ) {
    elementLines[0]->SetTrack2Value(QString("%1").arg(track2->Type));
    elementLines[1]->SetTrack2Value(track2->Name);
    elementLines[2]->SetTrack2Value(track2->TypeName);
    elementLines[3]->SetTrack2Value(track2->GroupName);
    elementLines[4]->SetTrack2Value(track2->NumofSamples);
    elementLines[5]->SetTrack2Value(track2->NumofCtrl);
    elementLines[6]->SetTrack2Value(track2->NumofAlarm);
    elementLines[7]->SetTrack2Value(track2->NumofSet);
    elementLines[8]->SetTrack2Value(track2->Related);
  }

  if ( track3 ) {
    elementLines[0]->SetTrack3Value(QString("%1").arg(track3->Type));
    elementLines[1]->SetTrack3Value(track3->Name);
    elementLines[2]->SetTrack3Value(track3->TypeName);
    elementLines[3]->SetTrack3Value(track3->GroupName);
    elementLines[4]->SetTrack3Value(track3->NumofSamples);
    elementLines[5]->SetTrack3Value(track3->NumofCtrl);
    elementLines[6]->SetTrack3Value(track3->NumofAlarm);
    elementLines[7]->SetTrack3Value(track3->NumofSet);
    elementLines[8]->SetTrack3Value(track3->Related);
  }

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Compare();
  }
}
