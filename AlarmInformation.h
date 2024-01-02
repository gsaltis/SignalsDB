/*****************************************************************************
 * FILE NAME    : AlarmInformation.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _alarminformation_h_
#define _alarminformation_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalsInformation.h"
#include "NCUAlarmSignal.h"
#include "sqlite3.h"
#include "AlarmSignalPair.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : AlarmInformation
 *****************************************************************************/
class AlarmInformation : public SignalsInformation
{
  Q_OBJECT;

 //! Constructors
 public :
  AlarmInformation          ();

 //! Destructor
 public :
  ~AlarmInformation         ();

 //! Public Methods
 public :
  void                          AddAlarm                (NCUAlarmSignal* InAlarm);
  NCUAlarmSignal*               FindAlarmByID           (int InTrack, int InID);
  void                          SQLRead                 (sqlite3* InDatabase);
  AlarmSignalPair*              FindPairByID            (int InID, int InSID);
  int                           GetTrackACount          (void);
  int                           GetTrackBCount          (void);
  int                           GetTrackAMissingCount   (void);
  int                           GetTrackBMissingCount   (void);
  void                          GetTrackDifferCount     (int &InSignalMajorCount, int &InMajorCount,
                                                         int &InSignalMinorCount, int &InMinorCount);
  int                           GetCountByTrack         (int InTrack);
  AlarmSignalPair*              GetPairByIndex          (int InIndex);
  int                           GetPairCount            (void);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          CreatePairs             (void);
  int                           GetTrackCount           (int InTrack);

 //! Private Data
 private :
  QList<NCUAlarmSignal*>        alarms;;
  QList<AlarmSignalPair*>       alarmPairs;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _alarminformation_h_*/
