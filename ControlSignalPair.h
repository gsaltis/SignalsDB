/*****************************************************************************
 * FILE NAME    : ControlSignalPair.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _controlsignalpair_h_
#define _controlsignalpair_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUControlSignal.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : ControlSignalPair
 *****************************************************************************/
class ControlSignalPair : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  ControlSignalPair           (int InID, int SID, NCUControlSignal* InTrack2Signal, NCUControlSignal* InTrack3Signal);

 //! Destructor
 public :
  ~ControlSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrack3Signal         (NCUControlSignal* InTrack3);
  NCUControlSignal*             GetTrack2               ();
  NCUControlSignal*             GetTrack3               ();
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
  NCUControlSignal*             Track2Signal;
  NCUControlSignal*             Track3Signal;
  int                           id;
  int                           sid;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _controlsignalpair_h_*/
