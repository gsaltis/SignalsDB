/*****************************************************************************
 * FILE NAME    : ElementDisplayLine.cpp
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
#include "ElementDisplayLine.h"

/*****************************************************************************!
 * Function : ElementDisplayLine
 *****************************************************************************/
ElementDisplayLine::ElementDisplayLine
(QString InLabelText, QColor InBackgroundColor) : QWidget()
{
  QPalette                              pal;

  labelText = InLabelText;
  backgroundColor = InBackgroundColor;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);

  initialize();
}

/*****************************************************************************!
 * Function : ~ElementDisplayLine
 *****************************************************************************/
ElementDisplayLine::~ElementDisplayLine
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
ElementDisplayLine::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
ElementDisplayLine::CreateSubWindows()
{
  int                                   x1;
  int                                   lineHeight = ELEMENT_DISPLAY_LINE_HEIGHT;;
  int                                   labelWidth = 180;
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  QPalette                              pal;
  
  x1 = 0;


  label = new QLabel(this);
  label->move(x1, 0);
  label->resize(labelWidth, lineHeight);
  label->setFont(labelFont);
  label->setText(labelText + QString(" : "));
  label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  pal = label->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(backgroundColor)));
  label->setPalette(pal);
  label->setAutoFillBackground(true);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
ElementDisplayLine::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
ElementDisplayLine::resizeEvent
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
