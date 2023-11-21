/*****************************************************************************
 * FILE NAME    : SignalStatsWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _signalstatswindow_h_
#define _signalstatswindow_h_

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

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SIGNAL_STATS_WINDOW_HEIGHT      60

/*****************************************************************************!
 * Exported Class : SignalStatsWindow
 *****************************************************************************/
class SignalStatsWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SignalStatsWindow             ();

 //! Destructor
 public :
  ~SignalStatsWindow            ();

 //! Public Methods
 public :

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
  void                          CreateSimpleLabel       (QString InText, int InX, int InY, int InWidth, int InHeight);
  QLabel*                       CreateDisplayLabel      (int InX, int InY, int InWidth, int InHeight);
  

 //! Private Data
 private :
  QLabel*                       Track2TotalLabel;
  QLabel*                       Track3TotalLabel;
  QLabel*                       Track2DifferLabel;
  QLabel*                       Track3DifferLabel;
  QLabel*                       Track2MissingLabel;
  QLabel*                       Track3MissingLabel;
  
  int                           Track2TotalSignals;
  int                           Track3TotalSignals;
  int                           Track2DifferSignals;
  int                           Track3DifferSignals;
  int                           Track2MissingSignals;
  int                           Track3MissingSignals;
  
 //! Public Slots
 public slots :
  void                          SlotSetTrack2Totals     (int InSignals);
  void                          SlotSetTrack3Totals     (int InSignals);
  void                          SlotSetTrack2Differs    (int InSignals);
  void                          SlotSetTrack3Differs    (int InSignals);
  void                          SlotSetTrack2Missing    (int InSignals);
  void                          SlotSetTrack3Missing    (int InSignals);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _signalstatswindow_h_*/
