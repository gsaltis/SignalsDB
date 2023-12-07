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
  AlarmSignalPair           (int InID, int SID, NCUAlarmSignal* InTrack2Signal, NCUAlarmSignal* InTrack3Signal);

 //! Destructor
 public :
  ~AlarmSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrack3Signal         (NCUAlarmSignal* InTrack3);
  NCUAlarmSignal*               GetTrack2               ();
  NCUAlarmSignal*               GetTrack3               ();
  bool                          Differ                  ();

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
  NCUAlarmSignal*               Track2Signal;
  NCUAlarmSignal*               Track3Signal;
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
