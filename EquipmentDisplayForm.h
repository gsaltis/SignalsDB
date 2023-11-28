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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalDisplayForm.h"

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

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _equipmentdisplayform_h_*/
