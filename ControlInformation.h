/*****************************************************************************
 * FILE NAME    : ControlInformation.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _controlinformation_h_
#define _controlinformation_h_

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
#include "NCUControlSignal.h"
#include "sqlite3.h"
#include "ControlSignalPair.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : ControlInformation
 *****************************************************************************/
class ControlInformation : public SignalsInformation
{
  Q_OBJECT;

 //! Constructors
 public :
  ControlInformation          ();

 //! Destructor
 public :
  ~ControlInformation         ();

 //! Public Methods
 public :
  void                          AddControl              (NCUControlSignal* InControl);
  NCUControlSignal*             FindControlByID         (int InTrack, int InID);
  void                          SQLRead                 (sqlite3* InDatabase);
  ControlSignalPair*            FindPairByID            (int InID, int InSID);
  int                           GetTrack2Count          (void);
  int                           GetTrack3Count          (void);
  int                           GetTrack2MissingCount   (void);
  int                           GetTrack3MissingCount   (void);
  int                           GetTrackDifferCount     (void);
  int                           GetCountByTrack         (int InTrack);
  ControlSignalPair*            GetPairByIndex          (int InIndex);
  int                           GetPairCount            (void);
  void                          GetTrackDifferCount     (int &InSignalMajorCount, int &InMajorCount,
                                                         int &InSignalMinorCount, int &InMinorCount);
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
  QList<NCUControlSignal*>      controls;;
  QList<ControlSignalPair*>     controlPairs;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _controlinformation_h_*/
