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
#include <xlnt/xlnt.hpp>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NCUSampleSignal.h"
#include "ElementDisplayLineFormat.h"

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
  SampleSignalPair           (int InID, int SID, NCUSampleSignal* InTrackASignal, NCUSampleSignal* InTrackBSignal);

 //! Destructor
 public :
  ~SampleSignalPair          ();

 //! Public Methods
 public :
  int                           GetID                   ();
  int                           GetSID                  ();
  void                          AddTrackBSignal         (NCUSampleSignal* InTrackB);
  NCUSampleSignal*              GetTrackA               ();
  NCUSampleSignal*              GetTrackB               ();
  bool                          Differ                  ();
  bool                          Differ                  (QString InTag);
  void                          GetDifferCounts         (int &InMajor, int &InMinor, QList<ElementDisplayLineFormat*> InFormats);
  int                           AddXCLFullRows          (xlnt::worksheet* InWorksheet, int InStartingRow);
  int                           AddXCLMajorDifferRows   (xlnt::worksheet* InWorksheet, int InStartingRow);

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
  NCUSampleSignal*              TrackASignal;
  NCUSampleSignal*              TrackBSignal;
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
