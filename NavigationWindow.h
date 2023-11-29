/*****************************************************************************
 * FILE NAME    : NavigationWindow.h
 * DATE         : November 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _navigationwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QAction>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define NAVIGATION_WINDOW_HEIGHT        24

/*****************************************************************************!
 * Exported Class : NavigationWindow
 *****************************************************************************/
class NavigationWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  NavigationWindow              ();

 //! Destructor
 public :
  ~NavigationWindow             ();

 //! Public Methods
 public :
  int                           GetButtonHeight         (void);
  void                          SetButtonHeight         (int InButtonHeight);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QPushButton*                  NextDifferElementButton;
  QPushButton*                  PrevDifferElementButton;
  QPushButton*                  NextElementButton;
  QPushButton*                  XCLButton;
  QPushButton*                  PreviousElementButton;
  int                           buttonWidth;
  int                           buttonHeight;
  QFont                         TextFont;
  QLabel*                       IndexLabel;
  
  int                           currentSignalIndex;
  int                           signalCount;

 //! Public Slots
 public slots :
  void                          SlotNextElementButtonPushed       (void);
  void                          SlotNextDifferElementButtonPushed (void);
  void                          SlotPreviousElementButtonPushed   (void);
  void                          SlotSetSignalCount                (int InSignalCount);
  void                          SlotSetCurrentSignalIndex         (int InCurrentSignalIndex);
  void                          SlotXCLButtonPushed               (void);
  void                          SlotPrevDifferElementButtonPushed (void);


 //! Public Signals
 signals :
  void                          SignalNextElement       (void);
  void                          SignalPreviousElement   (void);
  void                          SignalNextDifferElement (void);
  void                          SignalPrevDifferElement (void);
  void                          SignalXCL               (void);

 //! Public Actions
 public :
  QAction*                      ActionNextElementButtonPushed;
  QAction*                      ActionPreviousElementButtonPushed;

};

#define _navigationwindow_h_

#endif /* _navigationwindow_h_*/
