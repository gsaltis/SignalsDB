/*****************************************************************************
 * FILE NAME    : EquipmentDisplayForm.h
 * DATE         : November 22 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _equipmentdisplayform_h_
#define _equipmentdisplayform_h_

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
#include "EquipmentInformation.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define EQUIPMENT_DISPLAY_FORM_X        200
#define EQUIPMENT_DISPLAY_FORM_Y        200
#define EQUIPMENT_DISPLAY_FORM_WIDTH    200
#define EQUIPMENT_DISPLAY_FORM_HEIGHT   200

/*****************************************************************************!
 * Exported Class : EquipmentDisplayForm
 *****************************************************************************/
class EquipmentDisplayForm : public SignalDisplayForm
{
  Q_OBJECT;

 //! Constructors
 public :
  EquipmentDisplayForm          ();

 //! Destructor
 public :
  ~EquipmentDisplayForm         ();

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
  void                          SetTrackInformation     (EquipmentSignalPair* InPair);

 //! Private Data
 private :
  NavigationWindow*             navigationWindow;
  EquipmentInformation*         equipmentInformation;
  QLabel*                       EquipmentIDLabel;
  int                           currentEquipIndex;
  QLabel*                       Track3Label;
  
 //! Public Slots
 public slots :
  void                          SlotNextElement         (int InMajorMinorFlags);
  void                          SlotPreviousElement     (int InMajorMinorFlags);
  void                          SlotFirstElement        (void);
  void                          SlotLastElement         (void);
  
 //! Public Signals
 signals :
  void                          SignalSetCurrentEquipmentIndex (int InCurrentEquipmentIndex);

 //! Public Actions
 public :

};

#endif /* _equipmentdisplayform_h_*/
