/*****************************************************************************
 * FILE NAME    : EquipmentDisplayForm.cpp
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
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "EquipmentDisplayForm.h"
#include "ElementDisplayLine.h"

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
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
EquipmentDisplayForm::CreateSubWindows()
{
  int                                   n;
  QLabel*                               label;
  ElementDisplayLine*                   elementLine;
  int                                   x1, x2, x3;
  int                                   y;
  int                                   labelWidth = 150;
  int                                   labelHeight = 20;
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  QSize                                 s = size();
  int                                   w = s.width();
  QList<QString>                        labelNames;
  QColor                                backgroundColors[] = {
    QColor(0xEC, 0xEC, 0xEC),
    QColor(0xEC, 0xEC, 0xEC)
  };
  labelNames << "Type ID"
             << "Name"
             << "Type Name"
             << "Group Name"
             << "Number of Samples"
             << "Number of Controls"
             << "Number of Alarms"
             << "Number of Settings"
             << "Related";

  x1 = 10;
  x2 = x1 + labelWidth + 20;
  x3 = x2 + labelWidth + 20;


  y = 30;
  
  label = new QLabel();
  label->setParent(this);
  label->move(x2, y);
  label->resize(labelWidth, labelHeight);
  label->setFont(labelFont);
  label->setText(QString("TRACK 2"));
  label->setAlignment(Qt::AlignLeft);
  
  label = new QLabel();
  label->setParent(this);
  label->move(x3, y);
  label->resize(labelWidth, labelHeight);
  label->setFont(labelFont);
  label->setText(QString("TRACK 3"));
  label->setAlignment(Qt::AlignLeft);

  y = 10;
  label = new QLabel();
  label->setParent(this);
  label->move(x1, y);
  label->resize(170, labelHeight);
  label->setFont(labelFont);
  label->setText(QString("Equipment ID : "));
  label->setAlignment(Qt::AlignRight);
  
  //!
  y = 55;
  n = 0;
  for ( auto i : labelNames ) {
    elementLine = new ElementDisplayLine(i, backgroundColors[n % 2]);
    elementLine->setParent(this);
    elementLine->move(0, y);
    elementLine->resize(w, ELEMENT_DISPLAY_LINE_HEIGHT);
    y += ELEMENT_DISPLAY_LINE_HEIGHT;
    elementLines << elementLine;
    n++;
  }
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
EquipmentDisplayForm::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
EquipmentDisplayForm::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;

  size = InEvent->size();
  width = size.width();

  for ( auto i : elementLines ) {
    i->resize(width, ELEMENT_DISPLAY_LINE_HEIGHT);
  }
}
