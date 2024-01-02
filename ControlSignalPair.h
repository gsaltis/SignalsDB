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
#include "ElementDisplayLineFormat.h"

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
  ControlSignalPair           (int InID, int SID, NCUControlSignal* InTrackASignal, NCUControlSignal* InTrackBSignal);

 //! Destructor
 public :
  ~ControlSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrackBSignal         (NCUControlSignal* InTrackB);
  NCUControlSignal*             GetTrackA               ();
  NCUControlSignal*             GetTrackB               ();
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
  NCUControlSignal*             TrackASignal;
  NCUControlSignal*             TrackBSignal;
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
