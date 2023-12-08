/*****************************************************************************
 * FILE NAME    : SampleInformation.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sampleinformation_h_
#define _sampleinformation_h_

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
#include "NCUSampleSignal.h"
#include "sqlite3.h"
#include "SampleSignalPair.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SampleInformation
 *****************************************************************************/
class SampleInformation : public SignalsInformation
{
  Q_OBJECT;

 //! Constructors
 public :
  SampleInformation          ();

 //! Destructor
 public :
  ~SampleInformation         ();

 //! Public Methods
 public :
  void                          AddSample               (NCUSampleSignal* InSample);
  NCUSampleSignal*              FindSampleByID          (int InTrack, int InID);
  void                          SQLRead                 (sqlite3* InDatabase);
  SampleSignalPair*             FindPairByID            (int InID, int InSID);
  int                           GetTrack2Count          (void);
  int                           GetTrack3Count          (void);
  int                           GetTrack2MissingCount   (void);
  int                           GetTrack3MissingCount   (void);
  int                           GetTrackDifferCount     (void);
  int                           GetCountByTrack         (int InTrack);
  SampleSignalPair*             GetPairByIndex          (int InIndex);
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
  QList<NCUSampleSignal*>      samples;;
  QList<SampleSignalPair*>     samplePairs;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sampleinformation_h_*/
