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
(QString InLabelText, QColor InBackgroundColor, QColor InValueColor) : QWidget()
{
  QPalette                              pal;

  labelText = InLabelText;
  backgroundColor = InBackgroundColor;
  SpacerColor = InBackgroundColor;
  SpacerWidth = 5;
  SignalLabelWidth = 240;
  ValueColor = InValueColor;
  
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);

  DifferColor = QColor(160, 0, 0);
  NormalColor = QColor(0, 0, 0);
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
  QPalette                              pal;
  int                                   x1;
  int                                   lineHeight = ELEMENT_DISPLAY_LINE_HEIGHT;;
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  QFont                                 dataFont = QFont("Segoe UI", 10, QFont::Normal);

  x1 = 0;
  SignalLabel = new QLabel(this);
  SignalLabel->move(x1, 0);
  SignalLabel->resize(SignalLabelWidth, lineHeight);
  SignalLabel->setFont(labelFont);
  SignalLabel->setText(labelText);
  SignalLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
  // SignalLabel->setMargin(4);
  SignalLabel->setIndent(5);

  pal = SignalLabel->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(backgroundColor)));
  SignalLabel->setPalette(pal);
  SignalLabel->setAutoFillBackground(true);

  //! Create label
  Track2Value = new QLabel();
  Track2Value->setParent(this);
  Track2Value->move(0, 0);
  Track2Value->resize(100, lineHeight);
  Track2Value->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  Track2Value->setFont(dataFont);
  Track2Value->setIndent(5);
  Track2Value->setAutoFillBackground(true);
  Track2Value->setWordWrap(true);
  
  Track3Value = new QLabel();
  Track3Value->setParent(this);
  Track3Value->move(0, 0);
  Track3Value->resize(100, lineHeight);
  Track3Value->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  Track3Value->setFont(dataFont);
  Track3Value->setIndent(5);
  Track3Value->setAutoFillBackground(true);
  Track3Value->setWordWrap(true);

  Spacer = new QLabel(this);
  Spacer->resize(SpacerWidth, size().height());
  Spacer->move(0, 0);
  Spacer->setAutoFillBackground(true);

  //!
  pal = Spacer->palette();
  pal.setBrush(QPalette::Window, QBrush(SpacerColor));
  Spacer->setPalette(pal);

  pal = Track2Value->palette();
  pal.setBrush(QPalette::Window, QBrush(ValueColor));
  Track2Value->setPalette(pal);

  pal = Track3Value->palette();
  pal.setBrush(QPalette::Window, QBrush(ValueColor));
  Track3Value->setPalette(pal);
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
  int                                   w;
  QSize					size;  
  int					width;
  int					height;

  int                                   track2X;
  int                                   track2Y;
  int                                   track2W;
  int                                   track2H;

  int                                   track3X;
  int                                   track3Y;
  int                                   track3W;
  int                                   track3H;

  int                                   signalLabelX;
  int                                   signalLabelY;
  int                                   signalLabelW;
  int                                   signalLabelH;

  int                                   spacerX;
  int                                   spacerY;
  int                                   spacerW;
  int                                   spacerH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  w = (width - (SignalLabelWidth + SpacerWidth)) / 2;

  //!
  signalLabelX = 0;
  signalLabelY = 0;
  signalLabelW = SignalLabelWidth;
  signalLabelH = height;
  
  track2X = SignalLabelWidth;
  track2Y = 0;
  track2H = height;
  track2W = w;

  spacerX = track2X + track2W;
  spacerY = 0;
  spacerH = height;
  spacerW = SpacerWidth;

  track3X = spacerX + spacerW;
  track3Y = 0;
  track3W = w;
  track3H = height;

  //!
  Track2Value->move(track2X, track2Y);
  Track2Value->resize(track2W, track2H);

  Spacer->move(spacerX, spacerY);
  Spacer->resize(spacerW, spacerH);

  Track3Value->move(track3X, track3Y);
  Track3Value->resize(track3W, track3H);

  SignalLabel->move(signalLabelX, signalLabelY);
  SignalLabel->resize(signalLabelW, signalLabelH);
}

/*****************************************************************************!
 * Function : SetTrack2Value
 *****************************************************************************/
void
ElementDisplayLine::SetTrack2Value
(QString InValue)
{
  Track2Value->setText(InValue);
}

/*****************************************************************************!
 * Function : SetTrack3Value
 *****************************************************************************/
void
ElementDisplayLine::SetTrack3Value
(QString InValue)
{
  Track3Value->setText(InValue);
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
ElementDisplayLine::Clear(void)
{
  Track2Value->setText("");
  Track3Value->setText("");
}

/*****************************************************************************!
 * Function : Compare
 *****************************************************************************/
void
ElementDisplayLine::Compare(void)
{
  QPalette                              pal;
  QFont                                 normalFont = QFont("Segoe UI", 10, QFont::Normal);
  QFont                                 differFont = QFont("Segoe UI", 10, QFont::Bold);
  
  pal = Track2Value->palette();
  pal.setBrush(QPalette::WindowText, QBrush(NormalColor));
  Track2Value->setPalette(pal);
  Track2Value->setFont(normalFont);

  pal = Track3Value->palette();
  pal.setBrush(QPalette::WindowText, QBrush(NormalColor));
  Track3Value->setPalette(pal);
  Track3Value->setFont(normalFont);

  if ( Track2Value->text() != Track3Value->text() ) {
    pal = Track2Value->palette();
    pal.setBrush(QPalette::WindowText, QBrush(DifferColor));
    Track2Value->setPalette(pal);
    Track2Value->setFont(differFont);
    
    pal = Track3Value->palette();
    pal.setBrush(QPalette::WindowText, QBrush(DifferColor));
    Track3Value->setPalette(pal);
    Track3Value->setFont(differFont);
  }
}
