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

  currentEquipIndex = 0;
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
ControlDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalNextDifferElement,
          this,
          ControlDisplayForm::SlotNextDifferElement);
  connect(navigationWindow,
          NavigationWindow::SignalPrevDifferElement,
          this,
          ControlDisplayForm::SlotPrevDifferElement);
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
 * Function : SlotNextElement
 *****************************************************************************/
void
ControlDisplayForm::SlotNextElement(void)
{
  ControlSignalPair*                  pair;
  if ( currentEquipIndex + 1 >= controlInformation->GetPairCount() ) {
    return;
  }

  currentEquipIndex++;
  pair = controlInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentControlIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SlotNextDifferElement
 *****************************************************************************/
void
ControlDisplayForm::SlotNextDifferElement(void)
{
  int                                   i, n;
  ControlSignalPair*                  pair;
  
  n = controlInformation->GetPairCount();

  for ( i = currentEquipIndex + 1 ; i < n ; i++ ) {
    pair = controlInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentControlIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPrevDifferElement
 *****************************************************************************/
void
ControlDisplayForm::SlotPrevDifferElement(void)
{
  int                                   i;
  ControlSignalPair*                  pair;
  
  for ( i = currentEquipIndex - 1; i >= 0 ; i-- ) {
    pair = controlInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentControlIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
ControlDisplayForm::SlotPreviousElement(void)
{
  ControlSignalPair*                  pair;
  if ( currentEquipIndex == 0 ) {
    return;
  }
  currentEquipIndex--;
  pair = controlInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
    emit SignalSetCurrentControlIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
ControlDisplayForm::SetTrackInformation
(ControlSignalPair* InPair)
{
  
  int                                   i;
  NCUControlSignal*                     track2;
  NCUControlSignal*                     track3;

  ControlIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines[i++]->SetTrack2Value(track2->CTRLName);
    elementLines[i++]->SetTrack2Value(track2->Unit);
    elementLines[i++]->SetTrack2Value(track2->SIndx);
    elementLines[i++]->SetTrack2Value(track2->SChan);
    elementLines[i++]->SetTrack2Value(track2->ValType);
    elementLines[i++]->SetTrack2Value(track2->Defaults);
    elementLines[i++]->SetTrack2Value(track2->Range);
    elementLines[i++]->SetTrack2Value(track2->DisplayAttr);
    elementLines[i++]->SetTrack2Value(track2->CtrlAttr);
    elementLines[i++]->SetTrack2Value(track2->Threshold);
    elementLines[i++]->SetTrack2Value(track2->CableExpRPN);
    elementLines[i++]->SetTrack2Value(track2->CableExpFull);
    elementLines[i++]->SetTrack2Value(track2->Auth);
    elementLines[i++]->SetTrack2Value(track2->DisplayID);
    elementLines[i++]->SetTrack2Value(track2->DispFmt);
    elementLines[i++]->SetTrack2Value(track2->ChID);
    elementLines[i++]->SetTrack2Value(track2->CStep);
    elementLines[i++]->SetTrack2Value(track2->CParam);
    elementLines[i++]->SetTrack2Value(track2->CexpRPN);
    elementLines[i++]->SetTrack2Value(track2->CexpFullDispExp);
    elementLines[i++]->SetTrack2Value(track2->States);
    elementLines[i++]->SetTrack2Value(track2->CAction);
  }

  if ( track3 ) {
    i = 0;
    elementLines[i++]->SetTrack3Value(track3->CTRLName);
    elementLines[i++]->SetTrack3Value(track3->Unit);
    elementLines[i++]->SetTrack3Value(track3->SIndx);
    elementLines[i++]->SetTrack3Value(track3->SChan);
    elementLines[i++]->SetTrack3Value(track3->ValType);
    elementLines[i++]->SetTrack3Value(track3->Defaults);
    elementLines[i++]->SetTrack3Value(track3->Range);
    elementLines[i++]->SetTrack3Value(track3->DisplayAttr);
    elementLines[i++]->SetTrack3Value(track3->CtrlAttr);
    elementLines[i++]->SetTrack3Value(track3->Threshold);
    elementLines[i++]->SetTrack3Value(track3->CableExpRPN);
    elementLines[i++]->SetTrack3Value(track3->CableExpFull);
    elementLines[i++]->SetTrack3Value(track3->Auth);
    elementLines[i++]->SetTrack3Value(track3->DisplayID);
    elementLines[i++]->SetTrack3Value(track3->DispFmt);
    elementLines[i++]->SetTrack3Value(track3->ChID);
    elementLines[i++]->SetTrack3Value(track3->CStep);
    elementLines[i++]->SetTrack3Value(track3->CParam);
    elementLines[i++]->SetTrack3Value(track3->CexpRPN);
    elementLines[i++]->SetTrack3Value(track3->CexpFullDispExp);
    elementLines[i++]->SetTrack3Value(track3->States);
    elementLines[i++]->SetTrack3Value(track3->CAction);
  }

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Compare();
  }
}
