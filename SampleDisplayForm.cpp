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

  currentEquipIndex = 0;
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
  int                                   n;
  QLabel*                               label;
  ElementDisplayLine*                   elementLine;
  int                                   x1, x2, x3;
  int                                   y;
  int                                   labelWidth = 210;
  int                                   labelHeight = 20;
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  QFont                                 valueFont = QFont("Segoe UI", 10, QFont::Normal);
  QSize                                 s = size();
  int                                   w = s.width();
  QList<QString>                        labelNames;
  QColor                                backgroundColors[] = {
    QColor(0xEC, 0xEC, 0xEC),
    QColor(0xEC, 0xEC, 0xEC)
  };


  labelNames << "Sample Name"
             << "Unit"
             << "Signal Index"
             << "Signal Channel"
             << "Value Type"
             << "Stor Threshold"
             << "StorInt"
             << "Eval Expression RPN"
             << "Eval Expression Full"
             << "Range"
             << "Display Attribute"
             << "Display Level"
             << "Display ID"
             << "Display Format"
             << "Display Expression RPN"
             << "Display Expression Full"
             << "Enums";
  
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
  n = 0;
  for ( auto i : labelNames ) {
    elementLine = new ElementDisplayLine(i, backgroundColors[n % 2], ValueColors[n % 2]);
    elementLine->setParent(this);
    elementLine->move(0, y);
    elementLine->resize(w, ELEMENT_DISPLAY_LINE_HEIGHT);
    y += ELEMENT_DISPLAY_LINE_HEIGHT;
    elementLines << elementLine;
    n++;
  }

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
SampleDisplayForm::CreateConnections(void)
{
  connect(navigationWindow,
          NavigationWindow::SignalNextDifferElement,
          this,
          SampleDisplayForm::SlotNextDifferElement);
  connect(navigationWindow,
          NavigationWindow::SignalPrevDifferElement,
          this,
          SampleDisplayForm::SlotPrevDifferElement);
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
SampleDisplayForm::SlotNextElement(void)
{
  SampleSignalPair*                     pair;
  if ( currentEquipIndex + 1 >= sampleInformation->GetPairCount() ) {
    return;
  }

  currentEquipIndex++;
  pair = sampleInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);
  emit SignalSetCurrentSampleIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SlotNextDifferElement
 *****************************************************************************/
void
SampleDisplayForm::SlotNextDifferElement(void)
{
  int                                   i, n;
  SampleSignalPair*                     pair;
  
  n = sampleInformation->GetPairCount();

  for ( i = currentEquipIndex + 1 ; i < n ; i++ ) {
    pair = sampleInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentSampleIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPrevDifferElement
 *****************************************************************************/
void
SampleDisplayForm::SlotPrevDifferElement(void)
{
  int                                   i;
  SampleSignalPair*                     pair;
  
  for ( i = currentEquipIndex - 1; i >= 0 ; i-- ) {
    pair = sampleInformation->GetPairByIndex(i);
    if ( ! pair->Differ() ) {
      continue;
    }
    currentEquipIndex = i;
    emit SignalSetCurrentSampleIndex(currentEquipIndex + 1);
    SetTrackInformation(pair);
    return;
  }
}

/*****************************************************************************!
 * Function : SlotPreviousElement
 *****************************************************************************/
void
SampleDisplayForm::SlotPreviousElement(void)
{
  SampleSignalPair*                  pair;
  if ( currentEquipIndex == 0 ) {
    return;
  }
  currentEquipIndex--;
  pair = sampleInformation->GetPairByIndex(currentEquipIndex);
  SetTrackInformation(pair);  
    emit SignalSetCurrentSampleIndex(currentEquipIndex + 1);
}

/*****************************************************************************!
 * Function : SetTrackInformation
 *****************************************************************************/
void
SampleDisplayForm::SetTrackInformation
(SampleSignalPair* InPair)
{
  
  int                                   i;
  NCUSampleSignal*                      track2;
  NCUSampleSignal*                      track3;

  SampleIDLabel->setText(QString("%1").arg(InPair->GetID()));
  SignalIDLabel->setText(QString("%1").arg(InPair->GetSID()));
  
  track2 = InPair->GetTrack2();
  track3 = InPair->GetTrack3();

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Clear();
  }

  if ( track2 ) {
    i = 0;
    elementLines[i++]->SetTrack2Value(track2->SAMPLEName);
    elementLines[i++]->SetTrack2Value(track2->Unit);
    elementLines[i++]->SetTrack2Value(track2->SIndx);
    elementLines[i++]->SetTrack2Value(track2->SChan);
    elementLines[i++]->SetTrack2Value(track2->ValType);
    elementLines[i++]->SetTrack2Value(track2->StorThreshold);
    elementLines[i++]->SetTrack2Value(track2->StorInt);
    elementLines[i++]->SetTrack2Value(track2->EvalExpRPN);
    elementLines[i++]->SetTrack2Value(track2->EvalExpFull);
    elementLines[i++]->SetTrack2Value(track2->Range);
    elementLines[i++]->SetTrack2Value(track2->DisplayAttr);
    elementLines[i++]->SetTrack2Value(track2->DisplayLvl);
    elementLines[i++]->SetTrack2Value(track2->DisplayID);
    elementLines[i++]->SetTrack2Value(track2->DispFmt);
    elementLines[i++]->SetTrack2Value(track2->DispExpRPN);
    elementLines[i++]->SetTrack2Value(track2->DispExpFull);
    elementLines[i++]->SetTrack2Value(track2->Enums);
  }

  if ( track3 ) {
    i = 0;
    elementLines[i++]->SetTrack3Value(track3->SAMPLEName);
    elementLines[i++]->SetTrack3Value(track3->Unit);
    elementLines[i++]->SetTrack3Value(track3->SIndx);
    elementLines[i++]->SetTrack3Value(track3->SChan);
    elementLines[i++]->SetTrack3Value(track3->ValType);
    elementLines[i++]->SetTrack3Value(track3->StorThreshold);
    elementLines[i++]->SetTrack3Value(track3->StorInt);
    elementLines[i++]->SetTrack3Value(track3->EvalExpRPN);
    elementLines[i++]->SetTrack3Value(track3->EvalExpFull);
    elementLines[i++]->SetTrack3Value(track3->Range);
    elementLines[i++]->SetTrack3Value(track3->DisplayAttr);
    elementLines[i++]->SetTrack3Value(track3->DisplayLvl);
    elementLines[i++]->SetTrack3Value(track3->DisplayID);
    elementLines[i++]->SetTrack3Value(track3->DispFmt);
    elementLines[i++]->SetTrack3Value(track3->DispExpRPN);
    elementLines[i++]->SetTrack3Value(track3->DispExpFull);
    elementLines[i++]->SetTrack3Value(track3->Enums);
  }

  for ( i = 0 ; i < elementLines.size() ; i++ ) {
    elementLines[i]->Compare();
  }
}
