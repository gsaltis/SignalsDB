/*****************************************************************************
 * FILE NAME    : AlarmSignalPair.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _alarmsignalpair_h_
#define _alarmsignalpair_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUAlarmSignal.h"
#include"ElementDisplayLineFormat.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : AlarmSignalPair
 *****************************************************************************/
class AlarmSignalPair : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  AlarmSignalPair           (int InID, int SID, NCUAlarmSignal* InTrackASignal, NCUAlarmSignal* InTrackBSignal);

 //! Destructor
 public :
  ~AlarmSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrackBSignal         (NCUAlarmSignal* InTrack3);
  NCUAlarmSignal*               GetTrackA               ();
  NCUAlarmSignal*               GetTrackB               ();
  bool                          Differ                  ();
  bool                          Differ                  (QString InTag);
  void                          GetDifferCounts         (int &InMajor, int &InMinor, QList<ElementDisplayLineFormat*> InFormats);
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  NCUAlarmSignal*               TrackASignal;
  NCUAlarmSignal*               TrackBSignal;
  int                           id;
  int                           sid;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _alarmsignalpair_h_*/
