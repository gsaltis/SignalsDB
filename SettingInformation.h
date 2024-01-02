/*****************************************************************************
 * FILE NAME    : SettingInformation.h
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _settinginformation_h_
#define _settinginformation_h_

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
#include "NCUSettingSignal.h"
#include "sqlite3.h"
#include "SettingSignalPair.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SettingInformation
 *****************************************************************************/
class SettingInformation : public SignalsInformation
{
  Q_OBJECT;

 //! Constructors
 public :
  SettingInformation          ();

 //! Destructor
 public :
  ~SettingInformation         ();

 //! Public Methods
 public :
  void                          AddSetting              (NCUSettingSignal* InSetting);
  NCUSettingSignal*             FindSettingByID         (int InTrack, int InID);
  void                          SQLRead                 (sqlite3* InDatabase);
  SettingSignalPair*            FindPairByID            (int InID, int InSID);
  int                           GetTrackACount          (void);
  int                           GetTrackBCount          (void);
  int                           GetTrackAMissingCount   (void);
  int                           GetTrackBMissingCount   (void);
  int                           GetTrackDifferCount     (void);
  int                           GetCountByTrack         (int InTrack);
  SettingSignalPair*            GetPairByIndex          (int InIndex);
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
  QList<NCUSettingSignal*>      settings;;
  QList<SettingSignalPair*>     settingPairs;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _settinginformation_h_*/
