/*****************************************************************************
 * FILE NAME    : SampleSignalPair.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _samplesignalpair_h_
#define _samplesignalpair_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUSampleSignal.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SampleSignalPair
 *****************************************************************************/
class SampleSignalPair : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SampleSignalPair           (int InID, int SID, NCUSampleSignal* InTrack2Signal, NCUSampleSignal* InTrack3Signal);

 //! Destructor
 public :
  ~SampleSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrack3Signal         (NCUSampleSignal* InTrack3);
  NCUSampleSignal*             GetTrack2               ();
  NCUSampleSignal*             GetTrack3               ();
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
  NCUSampleSignal*              Track2Signal;
  NCUSampleSignal*              Track3Signal;
  int                           id;
  int                           sid;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _samplesignalpair_h_*/
