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
#include <QCheckBox>
#include <QAction>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define NAVIGATION_WINDOW_HEIGHT        32
#define NAVIGATION_MAJOR_FLAG           1
#define NAVIGATION_MINOR_FLAG           2
#define NAVIGATION_MISSING_FLAG         4

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
  QPushButton*                  NextElementButton;
  QPushButton*                  XCLButton;
  QPushButton*                  EndButton;
  QPushButton*                  HomeButton;
  QPushButton*                  PreviousElementButton;
  int                           buttonWidth;
  int                           buttonHeight;
  QFont                         TextFont;
  QLabel*                       IndexLabel;
  
  int                           currentSignalIndex;
  int                           signalCount;
  QCheckBox*                    MajorCheckBox;
  QCheckBox*                    MinorCheckBox;
  QCheckBox*                    MissingCheckBox;
  int                           MajorMinorFlags;
  QFont                         CheckBoxFont;

 //! Public Slots
 public slots :
  void                          SlotNextElementButtonPushed     (void);
  void                          SlotPreviousElementButtonPushed (void);
  void                          SlotSetSignalCount              (int InSignalCount);
  void                          SlotSetCurrentSignalIndex       (int InCurrentSignalIndex);
  void                          SlotXCLButtonPushed             (void);
  void                          SlotEndButtonPushed             (void);
  void                          SlotHomeButtonPushed            (void);

  void                          SlotMajorCheckToggle            (int InChecked);
  void                          SlotMinorCheckToggle            (int InChecked);
  void                          SlotMissingCheckToggle          (int InChecked);

 //! Public Signals
 signals :
  void                          SignalNextElement       (int InMajorMinorFlags);
  void                          SignalPreviousElement   (int InMajorMinorFlags);
  void                          SignalXCL               (void);
  void                          SignalFirstElement      (void);
  void                          SignalLastElement       (void);

 //! Public Actions
 public :
  QAction*                      ActionNextElementButtonPushed;
  QAction*                      ActionPreviousElementButtonPushed;

};

#define _navigationwindow_h_

#endif /* _navigationwindow_h_*/
