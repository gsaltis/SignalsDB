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
  labelText = InLabelText;
  backgroundColor = InBackgroundColor;
  ValueColor = InValueColor;
  differType = Major;
  initialize();
}

/*****************************************************************************!
 * Function : ElementDisplayLine
 *****************************************************************************/
ElementDisplayLine::ElementDisplayLine
(QString InLabelText, QColor InBackgroundColor, QColor InValueColor, ElementDisplayLine::DifferLevel InDifferLevel) : QWidget()
{
  labelText = InLabelText;
  backgroundColor = InBackgroundColor;
  ValueColor = InValueColor;
  differType = InDifferLevel;
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
  QPalette                              pal;

  SpacerColor = backgroundColor;
  SpacerWidth = 5;
  SignalLabelWidth = 240;
  
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);

  DifferMajorColor = QColor(160, 0, 0);
  DifferMinorColor = QColor(0, 0, 160);
  NormalColor = QColor(0, 0, 0);
  
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
  TrackAValue = new QLabel();
  TrackAValue->setParent(this);
  TrackAValue->move(0, 0);
  TrackAValue->resize(100, lineHeight);
  TrackAValue->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  TrackAValue->setFont(dataFont);
  TrackAValue->setIndent(5);
  TrackAValue->setAutoFillBackground(true);
  TrackAValue->setWordWrap(true);
  
  TrackBValue = new QLabel();
  TrackBValue->setParent(this);
  TrackBValue->move(0, 0);
  TrackBValue->resize(100, lineHeight);
  TrackBValue->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  TrackBValue->setFont(dataFont);
  TrackBValue->setIndent(5);
  TrackBValue->setAutoFillBackground(true);
  TrackBValue->setWordWrap(true);

  Spacer = new QLabel(this);
  Spacer->resize(SpacerWidth, size().height());
  Spacer->move(0, 0);
  Spacer->setAutoFillBackground(true);

  //!
  pal = Spacer->palette();
  pal.setBrush(QPalette::Window, QBrush(SpacerColor));
  Spacer->setPalette(pal);

  pal = TrackAValue->palette();
  pal.setBrush(QPalette::Window, QBrush(ValueColor));
  TrackAValue->setPalette(pal);

  pal = TrackBValue->palette();
  pal.setBrush(QPalette::Window, QBrush(ValueColor));
  TrackBValue->setPalette(pal);
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
  TrackAValue->move(track2X, track2Y);
  TrackAValue->resize(track2W, track2H);

  Spacer->move(spacerX, spacerY);
  Spacer->resize(spacerW, spacerH);

  TrackBValue->move(track3X, track3Y);
  TrackBValue->resize(track3W, track3H);

  SignalLabel->move(signalLabelX, signalLabelY);
  SignalLabel->resize(signalLabelW, signalLabelH);
}

/*****************************************************************************!
 * Function : SetTrackAValue
 *****************************************************************************/
void
ElementDisplayLine::SetTrackAValue
(QString InValue)
{
  TrackAValue->setText(InValue);
}

/*****************************************************************************!
 * Function : SetTrackBValue
 *****************************************************************************/
void
ElementDisplayLine::SetTrackBValue
(QString InValue)
{
  TrackBValue->setText(InValue);
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
ElementDisplayLine::Clear(void)
{
  TrackAValue->setText("");
  TrackBValue->setText("");
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
  
  pal = TrackAValue->palette();
  pal.setBrush(QPalette::WindowText, QBrush(NormalColor));
  TrackAValue->setPalette(pal);
  TrackAValue->setFont(normalFont);

  pal = TrackBValue->palette();
  pal.setBrush(QPalette::WindowText, QBrush(NormalColor));
  TrackBValue->setPalette(pal);
  TrackBValue->setFont(normalFont);

  if ( TrackAValue->text() != TrackBValue->text() ) {
    pal = TrackAValue->palette();
    pal.setBrush(QPalette::WindowText, differType == Major ? QBrush(DifferMajorColor) : QBrush(DifferMinorColor));
    TrackAValue->setPalette(pal);
    TrackAValue->setFont(differFont);
    
    pal = TrackBValue->palette();
    pal.setBrush(QPalette::WindowText, differType == Major ? QBrush(DifferMajorColor) : QBrush(DifferMinorColor));
    TrackBValue->setPalette(pal);
    TrackBValue->setFont(differFont);
  }
}

/*****************************************************************************!
 * Function : GetDifferType
 *****************************************************************************/
ElementDisplayLine::DifferLevel
ElementDisplayLine::GetDifferType(void)
{
  return differType;
}
