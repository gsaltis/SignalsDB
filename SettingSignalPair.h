/*****************************************************************************
 * FILE NAME    : SettingSignalPair.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _settingsignalpair_h_
#define _settingsignalpair_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUSettingSignal.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SettingSignalPair
 *****************************************************************************/
class SettingSignalPair : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SettingSignalPair           (int InID, int SID, NCUSettingSignal* InTrack2Signal, NCUSettingSignal* InTrack3Signal);

 //! Destructor
 public :
  ~SettingSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrack3Signal         (NCUSettingSignal* InTrack3);
  NCUSettingSignal*             GetTrack2               ();
  NCUSettingSignal*             GetTrack3               ();
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
  NCUSettingSignal*             Track2Signal;
  NCUSettingSignal*             Track3Signal;
  int                           id;
  int                           sid;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _settingsignalpair_h_*/
