/*****************************************************************************
 * FILE NAME    : SignalDisplayForm.cpp
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalDisplayForm.h"
#include "main.h"

/*****************************************************************************!
 * Function : SignalDisplayForm
 *****************************************************************************/
SignalDisplayForm::SignalDisplayForm
() : QWidget()
{
  QPalette pal;
  ValueColors[0] = QColor("#E5E7E9");
  ValueColors[1] = QColor("#D7DBDD");
  
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~SignalDisplayForm
 *****************************************************************************/
SignalDisplayForm::~SignalDisplayForm
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
SignalDisplayForm::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
SignalDisplayForm::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
SignalDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
SignalDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : AddElementLines
 *****************************************************************************/
void
SignalDisplayForm::AddElementLines
(QString InFormName, int &InY)
{
  int                                   w;
  int                                   y;
  ElementDisplayLineFormat*             lineFormat;
  QList<ElementDisplayLineFormat*>      lineFormats;
  int                                   n, m;
  ElementDisplayLine*                   elementLine;
  QColor                                backgroundColors[] = {
    QColor(0xEC, 0xEC, 0xEC),
    QColor(0xEC, 0xEC, 0xEC)
  };

  w = size().width();
  
  lineFormats = MainConfiguration->GetElementLineFormats(InFormName);

  y = InY;
  m = lineFormats.size();
  for ( n = 0 ; n < m ; n++ ) {
    lineFormat = lineFormats[n];
    elementLine = new ElementDisplayLine(lineFormat->GetElementName(), backgroundColors[n % 2], ValueColors[n % 2],
                                         lineFormat->GetDifferenceSeverity() == "Major"
                                         ? ElementDisplayLine::Major : ElementDisplayLine::Minor);
    elementLine->setParent(this);
    elementLine->move(0, y);
    elementLine->resize(w, ELEMENT_DISPLAY_LINE_HEIGHT * lineFormat->GetLineHeightMultiplier());
    elementLines << elementLine;
    if ( lineFormat->GetLineHeightMultiplier() == 0 ) {
      elementLine->hide();
    }
    y += ELEMENT_DISPLAY_LINE_HEIGHT * lineFormat->GetLineHeightMultiplier();
  }
  InY = y;
}

  
