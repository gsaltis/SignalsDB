/*****************************************************************************
 * FILE NAME    : ConfigurationDialog.h
 * DATE         : January 03 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _configurationdialog_h_
#define _configurationdialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CONFIGURATION_DIALOG_WIDTH              800
#define CONFIGURATION_DIALOG_HEIGHT             360

/*****************************************************************************!
 * Exported Class : ConfigurationDialog
 *****************************************************************************/
class ConfigurationDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  ConfigurationDialog           ();

 //! Destructor
 public :
  ~ConfigurationDialog          ();

 //! Public Methods
 public :

 //! Public Data
 public :
  QGroupBox*                    InstallationFrame;
  QGroupBox*                    TracksFrame;

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);
  void                          CreateConnections       (void);
  void                          CreateSubWindows        (void);
  void                          CreateInstallationFrame (void);
  void                          CreateTracksFrame       (void);
  QStringList                   TrackSelectionComboAddItems (void);
  void                          InitializeValues        (void);
  bool                          VerifyInfo              (void);

 //! Private Data
 private :
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;
  int                           LeftMargin;
  int                           RightMargin;
  QLabel*                       HeaderLabel;
  QLabel*                       MessageArea;
  QColor                        MessageAreaTextColor;
  QLabel*                       InstallDirectoryLabel;
  QLabel*                       DatabaseNameLabel;
  QLabel*                       TrackAVersionLabel;
  QLabel*                       TrackBVersionLabel;
  QLineEdit*                    InstallDirectoryNameEdit;
  QLineEdit*                    DatabaseNameEdit;
  QComboBox*                    TrackASelectionCombo;
  QComboBox*                    TrackBSelectionCombo;
  QPushButton*                  InstallFilenameBrowseButton;
  QPushButton*                  DatabaseNameBrowseButton;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();
  void                          slotTrackASelectionCombo_selected_item (int selected_index);
  void                          slotTrackBSelectionCombo_selected_item (int selected_index);
  void                          SlotInstallFilenameBrowseButtonPushed (void);
  void                          SlotDatabaseNameBrowseButtonPushed (void);

 //! Public Signals
 signals :

 //! Public Actions
 public :
  QAction*                      ActionInstallFilenameBrowseButtonPushed;
  QAction*                      ActionDatabaseNameBrowseButtonPushed;

};

#endif /* _configurationdialog_h_*/
