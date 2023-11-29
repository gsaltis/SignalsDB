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
  buttonHeight = 24;
  buttonWidth = 24;
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
  XCLButton->resize(32,32);
  XCLButton->setIcon(QIcon(QPixmap(":/Images/XCL.png")));
  connect(XCLButton, SIGNAL(pressed()), this, SLOT(SlotXCLButtonPushed()));

  //! Create the NextElementButton button  
  NextElementButton = new QPushButton();
  NextElementButton->setParent(this);
  NextElementButton->move(0, 0);
  NextElementButton->resize(32,32);
  NextElementButton->setIcon(QIcon(QPixmap(":/Images/Right.png")));
  connect(NextElementButton, SIGNAL(pressed()), this, SLOT(SlotNextElementButtonPushed()));
  
  //! Create the NextElementButton button  
  NextDifferElementButton = new QPushButton();
  NextDifferElementButton->setParent(this);
  NextDifferElementButton->move(0, 0);
  NextDifferElementButton->resize(32,32);
  NextDifferElementButton->setIcon(QIcon(QPixmap(":/Images/DoubleRight.png")));
  connect(NextDifferElementButton, SIGNAL(pressed()), this, SLOT(SlotNextDifferElementButtonPushed()));

  //! Create the NextElementButton button  
  PrevDifferElementButton = new QPushButton();
  PrevDifferElementButton->setParent(this);
  PrevDifferElementButton->move(0, 0);
  PrevDifferElementButton->resize(32,32);
  PrevDifferElementButton->setIcon(QIcon(QPixmap(":/Images/DoubleLeft.png")));
  connect(PrevDifferElementButton, SIGNAL(pressed()), this, SLOT(SlotPrevDifferElementButtonPushed()));
  
  //! Create the PreviousElementButton button
  PreviousElementButton = new QPushButton();
  PreviousElementButton->setParent(this);
  PreviousElementButton->move(0, 0);
  PreviousElementButton->resize(32,32);
  PreviousElementButton->setIcon(QIcon(QPixmap(":/Images/Left.png")));
  connect(PreviousElementButton, SIGNAL(pressed()), this, SLOT(SlotPreviousElementButtonPushed()));

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
  QSize                                 s;
  int                                   nextX;
  int                                   nextY;
  int                                   nextW;
  int                                   nextH;

  int                                   nextDifferX;
  int                                   nextDifferY;
  int                                   nextDifferW;
  int                                   nextDifferH;

  int                                   prevDifferX;
  int                                   prevDifferY;
  int                                   prevDifferW;
  int                                   prevDifferH;

  int                                   prevX;
  int                                   prevY;
  int                                   prevW;
  int                                   prevH;

  int                                   htmX;
  int                                   htmY;
  int                                   htmW;
  int                                   htmH;

  int                                   indexlabelX;
  int                                   indexlabelY;
  int                                   indexlabelW;
  int                                   indexlabelH;
  
  int                                   horizontalSkip = 1;
  int                                   width;
  int                                   height;
  
  s = InEvent->size();
  width = s.width();
  height = s.height();
  
  //!
  htmX = 0;
  htmY = 0;
  htmW = buttonWidth;
  htmH = buttonHeight;

  prevDifferY = 0;
  prevDifferX = (buttonWidth + horizontalSkip) * 1;
  prevDifferW = buttonWidth;
  prevDifferH = buttonHeight;

  prevX = (buttonWidth + horizontalSkip) * 2;
  prevY = 0;
  prevW = buttonWidth;
  prevH = buttonHeight;

  nextY = 0;
  nextX = (buttonWidth + horizontalSkip) * 3;
  nextW = buttonWidth;
  nextH = buttonHeight;

  nextDifferY = 0;
  nextDifferX = (buttonWidth + horizontalSkip) * 4;
  nextDifferW = buttonWidth;
  nextDifferH = buttonHeight;

  indexlabelW = IndexLabel->size().width();
  indexlabelX = width - (indexlabelW + 5);
  indexlabelY = 0;
  indexlabelH = height;
  
  PreviousElementButton->move(prevX, prevY);
  PreviousElementButton->resize(prevW, prevH);

  NextElementButton->move(nextX, nextY);
  NextElementButton->resize(nextW, nextH);
  
  NextDifferElementButton->move(nextDifferX, nextDifferY);
  NextDifferElementButton->resize(nextDifferW, nextDifferH);

  PrevDifferElementButton->move(prevDifferX, prevDifferY);
  PrevDifferElementButton->resize(prevDifferW, prevDifferH);

  XCLButton->move(htmX, htmY);
  XCLButton->resize(htmW, htmH);

  IndexLabel->move(indexlabelX, indexlabelY);
  IndexLabel->resize(indexlabelW, indexlabelH);
}

/*****************************************************************************!
 * Function : SlotNextDifferElementButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotNextDifferElementButtonPushed(void)
{
  emit SignalNextDifferElement();
}

/*****************************************************************************!
 * Function : SlotPrevDifferElementButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotPrevDifferElementButtonPushed(void)
{
  emit SignalPrevDifferElement();
}

/*****************************************************************************!
 * Function : SlotNextElementButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotNextElementButtonPushed(void)
{
  emit SignalNextElement();
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
 * Function : SlotPreviousElementButtonPushed
 *****************************************************************************/
void
NavigationWindow::SlotPreviousElementButtonPushed(void)
{
  emit SignalPreviousElement();
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
