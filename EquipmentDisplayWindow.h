/*****************************************************************************
 * FILE NAME    : EquipmentDisplayWindow.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _equipmentdisplaywindow_h_
#define _equipmentdisplaywindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SignalDisplayWindow.h"
#include "EquipmentInformation.h"
#include "EquipmentDisplayForm.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define EQUIPMENT_DISPLAY_WINDOW_X      200
#define EQUIPMENT_DISPLAY_WINDOW_Y      200
#define EQUIPMENT_DISPLAY_WINDOW_WIDTH  200
#define EQUIPMENT_DISPLAY_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : EquipmentDisplayWindow
 *****************************************************************************/
class EquipmentDisplayWindow : public SignalDisplayWindow
{
  Q_OBJECT;

 //! Constructors
 public :
  EquipmentDisplayWindow        (QString InText);

 //! Destructor
 public :
  ~EquipmentDisplayWindow       ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          SetEquipmentInformation ();
  
 //! Private Data
 private :
  EquipmentInformation*         EquipmentInfo;
  
  EquipmentDisplayForm*         equipForm;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _equipmentdisplaywindow_h_*/
