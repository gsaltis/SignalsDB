/*****************************************************************************
 * FILE NAME    : NavigationWindow.cpp
 * DATE         : November 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QCheckBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NavigationWindow.h"

/*****************************************************************************!
 * Function : NavigationWindow
 *****************************************************************************/
NavigationWindow::NavigationWindow
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(208, 208, 208)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShape(QFrame::Box);
  setFrameShadow(QFrame::Raised);
  initialize();
}

/*****************************************************************************!
 * Function : ~NavigationWindow
 *****************************************************************************/
NavigationWindow::~NavigationWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
NavigationWindow::initialize()
{
  TextFont = QFont("Segoe UI", 10, QFont::Normal);
  CheckBoxFont = QFont("Segoe UI", 8, QFont::Normal);
  
  buttonHeight = 32;
  buttonWidth = 32;
  MajorMinorFlags = 0;
  InitializeSubWindows();  
  CreateSubWindows();
  ActionNextElementButtonPushed = new QAction("NextElementButtonPushed", this);
  connect(ActionNextElementButtonPushed, SIGNAL(triggered()), this, SLOT(SlotNextElementButtonPushed()));
  ActionPreviousElementButtonPushed = new QAction("PreviousElementButtonPushed", this);
  connect(ActionPreviousElementButtonPushed, SIGNAL(triggered()), this, SLOT(SlotPreviousElementButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
NavigationWindow::CreateSubWindows()
{
  //! Create the NextElementButton button  
  XCLButton = new QPushButton();
  XCLButton->setParent(this);
  XCLButton->move(0, 0);
  XCLButton->resize(buttonWidth,buttonHeight);
  XCLButton->setIcon(QIcon(QPixmap(":/Images/XCL.png")));
  connect(XCLButton, SIGNAL(pressed()), this, SLOT(SlotXCLButtonPushed()));

  HomeButton = new QPushButton();
  HomeButton->setParent(this);
  HomeButton->move(0, 0);
  HomeButton->resize(buttonWidth,buttonHeight);
  HomeButton->setText("H");
  connect(HomeButton, SIGNAL(pressed()), this, SLOT(SlotHomeButtonPushed()));

  EndButton = new QPushButton();
  EndButton->setParent(this);
  EndButton->move(0, 0);
  EndButton->resize(buttonWidth,buttonHeight);
  EndButton->setText("E");
  connect(EndButton, SIGNAL(pressed()), this, SLOT(SlotEndButtonPushed()));

  //! Create the NextElementButton button  
  NextElementButton = new QPushButton();
  NextElementButton->setParent(this);
  NextElementButton->move(0, 0);
  NextElementButton->resize(buttonWidth,buttonHeight);
  NextElementButton->setIcon(QIcon(QPixmap(":/Images/Right.png")));
  connect(NextElementButton, SIGNAL(pressed()), this, SLOT(SlotNextElementButtonPushed()));
  
  //! Create the PreviousElementButton button
  PreviousElementButton = new QPushButton();
  PreviousElementButton->setParent(this);
  PreviousElementButton->move(0, 0);
  PreviousElementButton->resize(buttonWidth,buttonHeight);
  PreviousElementButton->setIcon(QIcon(QPixmap(":/Images/Left.png")));
  connect(PreviousElementButton, SIGNAL(pressed()), this, SLOT(SlotPreviousElementButtonPushed()));

  MajorCheckBox = new QCheckBox("Major", this);
  MajorCheckBox->move(0, 0);
  MajorCheckBox->resize(100, 32);
  MajorCheckBox->setFont(CheckBoxFont);
  MajorCheckBox->setStyleSheet("QCheckBox::indicator { width:11px; height:11px }");
  connect(MajorCheckBox, QCheckBox::stateChanged, this, NavigationWindow::SlotMajorCheckToggle);
  
  MinorCheckBox = new QCheckBox("Minor", this);
  MinorCheckBox->move(0, 0);
  MinorCheckBox->resize(110, 32);
  MinorCheckBox->setFont(CheckBoxFont);
  MinorCheckBox->setStyleSheet("QCheckBox::indicator { width:11px; height:11px }");
  connect(MinorCheckBox, QCheckBox::stateChanged, this, NavigationWindow::SlotMinorCheckToggle);
  
  MissingCheckBox = new QCheckBox("Missing", this);
  MissingCheckBox->move(0, 0);
  MissingCheckBox->resize(100, 32);
  MissingCheckBox->setFont(CheckBoxFont);
  MissingCheckBox->setStyleSheet("QCheckBox::indicator { width:11px; height:11px }");
  connect(MissingCheckBox, QCheckBox::stateChanged, this, NavigationWindow::SlotMissingCheckToggle);
  
  IndexLabel = new QLabel(this);
  IndexLabel->move(0, 0);
  IndexLabel->resize(100, 20);
  IndexLabel->setFont(TextFont);
  IndexLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  IndexLabel->setText("0000 of 00000");
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
NavigationWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
NavigationWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   checkBoxWidth;
  int                                   checkBoxHeight;
  
  int                                   buttonPosition;
  QSize                                 s;
  int                                   nextX;
  int                                   nextY;
  int                                   nextW;
  int                                   nextH;

  int                                   prevX;
  int                                   prevY;
  int                                   prevW;
  int                                   prevH;

  int                                   xclX;
  int                                   xclY;
  int                                   xclW;
  int                                   xclH;

  int                                   homeX;
  int                                   homeY;
  int                                   homeW;
  int                                   homeH;

  int                                   endX;
  int                                   endY;
  int                                   endW;
  int                                   endH;

  int                                   majorX;
  int                                   majorY;
  int                                   majorW;
  int                                   majorH;
  
  int                                   minorX;
  int                                   minorY;
  int                                   minorW;
  int                                   minorH;
  
  int                                   missingX;
  int                                   missingY;
  int                                   missingW;
  int                                   missingH;
  
  int                                   indexlabelX;
  int                                   indexlabelY;
  int                                   indexlabelW;
  int                                   indexlabelH;
  
  int                                   horizontalSkip = 1;
  int                                   width;
  int                                   height;

  //!
  s = InEvent->size();
  width = s.width();
  height = s.height();
  checkBoxWidth = 70;
  checkBoxHeight = 13;
  
  //!
  xclX = 0;
  xclY = 0;
  xclW = buttonWidth;
  xclH = buttonHeight;

  buttonPosition = 1;
  homeX = (buttonWidth + horizontalSkip) * buttonPosition;;
  homeY = 0;
  homeW = buttonWidth;
  homeH = buttonHeight;
  buttonPosition++;
  
  prevX = (buttonWidth + horizontalSkip) * buttonPosition;
  prevY = 0;
  prevW = buttonWidth;
  prevH = buttonHeight;
  buttonPosition++;

  nextX = (buttonWidth + horizontalSkip) * buttonPosition;
  nextY = 0;
  nextW = buttonWidth;
  nextH = buttonHeight;
  buttonPosition++;

  endX = (buttonWidth + horizontalSkip) * buttonPosition;
  endY = 0;
  endW = buttonWidth;
  endH = buttonHeight;
  buttonPosition++;


  majorX = endX + endW + 20;
  majorY = 2;
  majorW = checkBoxWidth;
  majorH = checkBoxHeight;
  
  minorX = majorX;
  minorY = majorH + 3;;
  minorW = checkBoxWidth;
  minorH = checkBoxHeight;

  missingX = majorX + checkBoxWidth + 20;
  missingY = 2;
  missingW = checkBoxWidth;
  missingH = checkBoxHeight;
  
  indexlabelW = IndexLabel->size().width();
  indexlabelX = width - (indexlabelW + 5);
  indexlabelY = 0;
  indexlabelH = height;
  
  PreviousElementButton->move(prevX, prevY);
  PreviousElementButton->resize(prevW, prevH);

  NextElementButton->move(nextX, nextY);
  NextElementButton->resize(nextW, nextH);
  
  XCLButton->move(xclX, xclY);
  XCLButton->resize(xclW, xclH);

  HomeButton->move(homeX, homeY);
  HomeButton->resize(homeW, homeH);

  EndButton->move(endX, endY);
  EndButton->resize(endW, endH);

  IndexLabel->move(indexlabelX, indexlabelY);
  IndexLabel->resize(indexlabelW, indexlabelH);

  MajorCheckBox->move(majorX, majorY);
  MajorCheckBox->resize(majorW, majorH);

  MinorCheckBox->move(minorX, minorY);
  MinorCheckBox->resize(minorW, minorH);

  MissingCheckBox->move(missingX, missingY);
  MissingCheckBox->resize(missingW, missingH);
}

/*****************************************************************************!
 * Function : SlotXCLButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotXCLButtonPushed(void)
{
  emit SignalXCL();
}

/*****************************************************************************!
 * Function : SlotHomeButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotHomeButtonPushed(void)
{
  emit SignalFirstElement();
}

/*****************************************************************************!
 * Function : SlotEndButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotEndButtonPushed(void)
{
  emit SignalLastElement();
}

/*****************************************************************************!
 * Function : SlotNextElementButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotNextElementButtonPushed(void)
{
  emit SignalNextElement(MajorMinorFlags);
}

/*****************************************************************************!
 * Function : SlotPreviousElementButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotPreviousElementButtonPushed(void)
{
  emit SignalPreviousElement(MajorMinorFlags);
}

/*****************************************************************************!
 * Function : GetButtonHeight
 *****************************************************************************/
int
NavigationWindow::GetButtonHeight(void)
{
  return buttonHeight;  
}

/*****************************************************************************!
 * Function : SetButtonHeight
 *****************************************************************************/
void
NavigationWindow::SetButtonHeight
(int InButtonHeight)
{
  buttonHeight = InButtonHeight;  
}

/*****************************************************************************!
 * Function : SlotSetSignalCount
 *****************************************************************************/
void
NavigationWindow::SlotSetSignalCount
(int InSignalCount)
{
  signalCount = InSignalCount;
  IndexLabel->setText(QString("%1 of %2").arg(currentSignalIndex).arg(signalCount));
}

/*****************************************************************************!
 * Function : SlotSetCurrentSignalIndex
 *****************************************************************************/
void
NavigationWindow::SlotSetCurrentSignalIndex
(int InCurrentSignalIndex)
{
  currentSignalIndex = InCurrentSignalIndex;
  IndexLabel->setText(QString("%1 of %2").arg(currentSignalIndex).arg(signalCount));
}

/*****************************************************************************!
 * Function : SlotMajorCheckToggle
 *****************************************************************************/
void
NavigationWindow::SlotMajorCheckToggle
(int InChecked )
{
  int                           flag;

  flag = InChecked ? NAVIGATION_MAJOR_FLAG : 0;
  MajorMinorFlags = flag + (MajorMinorFlags & NAVIGATION_MINOR_FLAG);
  if ( InChecked ) {
    MissingCheckBox->setChecked(false);
  }
}

/*****************************************************************************!
 * Function : SlotMinorCheckToggle
 *****************************************************************************/
void
NavigationWindow::SlotMinorCheckToggle
(int InChecked )
{
  int                           flag;

  flag = InChecked ? NAVIGATION_MINOR_FLAG : 0;
  MajorMinorFlags = flag + (MajorMinorFlags & NAVIGATION_MAJOR_FLAG);
  if ( InChecked ) {
    MissingCheckBox->setChecked(false);
  }
}

/*****************************************************************************!
 * Function : SlotMissingCheckToggle
 *****************************************************************************/
void
NavigationWindow::SlotMissingCheckToggle
(int InChecked )
{
  if ( InChecked ) {
    MajorCheckBox->setChecked(false);
    MinorCheckBox->setChecked(false);
  }

  MajorMinorFlags = NAVIGATION_MISSING_FLAG;
}
