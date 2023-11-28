/*****************************************************************************
 * FILE NAME    : WindowHeader.cpp
 * DATE         : November 21 2023
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
#include "WindowHeader.h"

/*****************************************************************************!
 * Function : WindowHeader
 *****************************************************************************/
WindowHeader::WindowHeader
(QString InText, QWidget* InParent) : QWidget(InParent)
{
  QPalette pal;

  text = InText;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(0, 0, 0, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~WindowHeader
 *****************************************************************************/
WindowHeader::~WindowHeader
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
WindowHeader::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
WindowHeader::CreateSubWindows()
{

  //! Create label  
  TextLabel = new QLabel();
  TextLabel->setParent(this);
  TextLabel->move(0, 20);
  TextLabel->resize(175, 25);
  TextLabel->setText(text);
  TextLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
  TextLabel->setFont(QFont("Segoe UI", 20, QFont::Bold));
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
WindowHeader::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
WindowHeader::resizeEvent
(QResizeEvent* )
{
}
