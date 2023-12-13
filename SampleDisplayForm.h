/*****************************************************************************
 * FILE NAME    : SampleDisplayForm.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sampledisplayform_h_
#define _sampledisplayform_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalDisplayForm.h"
#include "NavigationWindow.h"
#include "SampleInformation.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define SAMPLE_DISPLAY_FORM_X        200
#define SAMPLE_DISPLAY_FORM_Y        200
#define SAMPLE_DISPLAY_FORM_WIDTH    200
#define SAMPLE_DISPLAY_FORM_HEIGHT   200

/*****************************************************************************!
 * Exported Class : SampleDisplayForm
 *****************************************************************************/
class SampleDisplayForm : public SignalDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  SampleDisplayForm          ();

 //! Destructor
 public :
  ~SampleDisplayForm         ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateConnections       (void);
  void                          SetTrackInformation     (SampleSignalPair* InPair);

  void                          SkipToNextMajorSignal   ();
  void                          SkipToNextMinorSignal   ();
  void                          SkipToNextAnySignal     ();
  void                          SkipToNextMissingSignal (int InMissingTracks);

  void                          SkipToPrevMajorSignal   ();
  void                          SkipToPrevMinorSignal   ();
  void                          SkipToPrevAnySignal     ();
  void                          SkipToPrevMissingSignal (int InMissingTracks);

  bool                          PairContainsMajorAlarm  (SampleSignalPair* InPair);
  bool                          PairContainsMinorAlarm  (SampleSignalPair* InPair);
  bool                          PairContainsAnyAlarm    (SampleSignalPair* InPair);
  bool                          PairContainsAlarm       (SampleSignalPair* InPair, ElementDisplayLine::DifferLevel InDifferType);
  
 //! Private Data
 private :
  NavigationWindow*             navigationWindow;
  SampleInformation*            sampleInformation;
  QLabel*                       SampleIDLabel;
  int                           currentSampleIndex;
  QLabel*                       Track3Label;
  QLabel*                       SignalIDLabel;

 //! Public Slots
 public slots :
  void                          SlotNextElement         (int InMajorMinorFlags);
  void                          SlotPreviousElement     (int InMajorMinorFlags);
  void                          SlotFirstElement        (void);
  void                          SlotLastElement         (void);
  
 //! Public Signals
 signals :
  void                          SignalSetCurrentSampleIndex (int InCurrentSampleIndex);

 //! Public Actions
 public :

};

#endif /* _sampledisplayform_h_*/
