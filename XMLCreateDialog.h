/*****************************************************************************
 * FILE NAME    : XMLCreateDialog.h
 * DATE         : December 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _xmlcreatedialog_h_
#define _xmlcreatedialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "XCLOptions.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define XMLCREATE_DIALOG_WIDTH                  600
#define XMLCREATE_DIALOG_HEIGHT                 400

/*****************************************************************************!
 * Exported Class : XMLCreateDialog
 *****************************************************************************/
class XMLCreateDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  XMLCreateDialog               (XCLOptions* InOptions);

 //! Destructor
 public :
  ~XMLCreateDialog              ();

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
  void                          Initialize              (void);
  void                          CreateConnections       (void);
  void                          CreateSubWindows        (void);
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QHash<QString, QCheckBox*>    CheckBoxes;
  
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;
  QWidget*                      LeftPane;
  QWidget*                      TopPane;
  int                           TopPaneHeight;

  QCheckBox*                    EquipmentAllCB;
  QCheckBox*                    EquipmentMajorCB;
  QCheckBox*                    EquipmentMinorCB;
  QCheckBox*                    EquipmentMissing2CB;
  QCheckBox*                    EquipmentMissing3CB;

  QCheckBox*                    SettingAllCB;
  QCheckBox*                    SettingMajorCB;
  QCheckBox*                    SettingMinorCB;
  QCheckBox*                    SettingMissing2CB;
  QCheckBox*                    SettingMissing3CB;

  QCheckBox*                    AlarmAllCB;
  QCheckBox*                    AlarmMajorCB;
  QCheckBox*                    AlarmMinorCB;
  QCheckBox*                    AlarmMissing2CB;
  QCheckBox*                    AlarmMissing3CB;

  QCheckBox*                    ControlAllCB;
  QCheckBox*                    ControlMajorCB;
  QCheckBox*                    ControlMinorCB;
  QCheckBox*                    ControlMissing2CB;
  QCheckBox*                    ControlMissing3CB;

  QCheckBox*                    SampleAllCB;
  QCheckBox*                    SampleMajorCB;
  QCheckBox*                    SampleMinorCB;
  QCheckBox*                    SampleMissing2CB;
  QCheckBox*                    SampleMissing3CB;

  QCheckBox*                    MinimalMajorCB;
  QCheckBox*                    MinimalMinorCB;
  
  QLineEdit*                    FileNameEdit;
  XCLOptions*                   Options;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _xmlcreatedialog_h_*/
