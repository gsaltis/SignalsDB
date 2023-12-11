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
EquipmentDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalFirstElement,
          this,
          EquipmentDisplayForm::SlotFirstElement);
  
  connect(navigationWindow,
          NavigationWindow::SignalLastElement,
          this,
          EquipmentDisplayForm::SlotLastElement);
  
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
EquipmentDisplayForm::SlotNextElement
(int)
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
 * Function : SlotPreviousElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotPreviousElement
(int)
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
  int                                   keysSize;
  QStringList                           keys;
  int                                   i;
  NCUEquipment*                         track2;
  NCUEquipment*                         track3;

  EquipmentIDLabel->setText(QString("%1").arg(InPair->GetID()));

  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  keys = elementLines.keys();
  keysSize = keys.size();
  for ( i = 0 ; i < keysSize ; i++ ) {
    elementLines[keys[i]]->Clear();
  }

  if ( track2 ) {
    elementLines["Type"]->SetTrack2Value(QString("%1").arg(track2->Type));
    elementLines["Name"]->SetTrack2Value(track2->Name);
    elementLines["TypeName"]->SetTrack2Value(track2->TypeName);
    elementLines["GroupName"]->SetTrack2Value(track2->GroupName);
    elementLines["NumofSamples"]->SetTrack2Value(track2->NumofSamples);
    elementLines["NumofCtrl"]->SetTrack2Value(track2->NumofCtrl);
    elementLines["NumofAlarm"]->SetTrack2Value(track2->NumofAlarm);
    elementLines["NumofSet"]->SetTrack2Value(track2->NumofSet);
    elementLines["Related"]->SetTrack2Value(track2->Related);
  }

  if ( track3 ) {
    elementLines["Type"]->SetTrack3Value(QString("%1").arg(track3->Type));
    elementLines["Name"]->SetTrack3Value(track3->Name);
    elementLines["TypeName"]->SetTrack3Value(track3->TypeName);
    elementLines["GroupName"]->SetTrack3Value(track3->GroupName);
    elementLines["NumofSamples"]->SetTrack3Value(track3->NumofSamples);
    elementLines["NumofCtrl"]->SetTrack3Value(track3->NumofCtrl);
    elementLines["NumofAlarm"]->SetTrack3Value(track3->NumofAlarm);
    elementLines["NumofSet"]->SetTrack3Value(track3->NumofSet);
    elementLines["Related"]->SetTrack3Value(track3->Related);
  }

  for ( i = 0 ; i < keysSize ; i++ ) {
    elementLines[keys[i]]->Compare();
  }
}

/*****************************************************************************!
 * Function : SlotFirstElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotFirstElement(void)
{
  EquipmentSignalPair*                  pair;
  currentEquipIndex = 0;
  pair = equipmentInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentEquipmentIndex(currentEquipIndex + 1);  
}

/*****************************************************************************!
 * Function : SlotLastElement
 *****************************************************************************/
void
EquipmentDisplayForm::SlotLastElement(void)
{
  EquipmentSignalPair*                  pair;
  currentEquipIndex = equipmentInformation->GetPairCount() - 1;
  pair = equipmentInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
  emit SignalSetCurrentEquipmentIndex(currentEquipIndex + 1);  
}
