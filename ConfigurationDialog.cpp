/*****************************************************************************
 * FILE NAME    : ConfigurationDialog.cpp
 * DATE         : January 03 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <QFileDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "ConfigurationDialog.h"
#include "main.h"

/*****************************************************************************!
 * Function : ConfigurationDialog
 *****************************************************************************/
ConfigurationDialog::ConfigurationDialog
() : QDialog()
{
  MessageAreaTextColor = QColor(212, 43, 54);
  Initialize();
}

/*****************************************************************************!
 * Function : ~ConfigurationDialog
 *****************************************************************************/
ConfigurationDialog::~ConfigurationDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
ConfigurationDialog::Initialize(void)
{
  CreateSubWindows();
  InitializeValues();
  CreateConnections();
  resize(CONFIGURATION_DIALOG_WIDTH, CONFIGURATION_DIALOG_HEIGHT);
  ActionInstallFilenameBrowseButtonPushed = new QAction("InstallFilenameBrowseButtonPushed", this);
  connect(ActionInstallFilenameBrowseButtonPushed, SIGNAL(triggered()), this, SLOT(SlotInstallFilenameBrowseButtonPushed()));
  ActionDatabaseNameBrowseButtonPushed = new QAction("DatabaseNameBrowseButtonPushed", this);
  connect(ActionDatabaseNameBrowseButtonPushed, SIGNAL(triggered()), this, SLOT(SlotDatabaseNameBrowseButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
ConfigurationDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
ConfigurationDialog::CreateSubWindows(void)
{
  QPalette                              pal;
  int                                   buttonHeight;
  int                                   buttonGap;
  int                                   cancelButtonX;
  int                                   okButtonX;
  int                                   buttonY;
  int                                   cancelButtonWidth;
  int                                   okButtonWidth;
  
  okButtonWidth = 60;
  cancelButtonWidth = 60;
  buttonGap = 5;
  buttonHeight = 20;
  okButtonX = CONFIGURATION_DIALOG_WIDTH - (okButtonWidth + cancelButtonWidth + (20 + buttonGap));
  cancelButtonX = CONFIGURATION_DIALOG_WIDTH - (cancelButtonWidth + 20);
  buttonY = CONFIGURATION_DIALOG_HEIGHT - (20 + buttonHeight);
 
  OKButton = new QPushButton();
  OKButton->setParent(this);
  OKButton->setText("OK");
  OKButton->move(okButtonX, buttonY);
  OKButton->resize(okButtonWidth, buttonHeight);
  
  CancelButton = new QPushButton();
  CancelButton->setParent(this);
  CancelButton->setText("Cancel");
  CancelButton->move(cancelButtonX, buttonY);
  CancelButton->resize(cancelButtonWidth, buttonHeight);
  CreateInstallationFrame();
  CreateTracksFrame();

  //! Create label
  HeaderLabel = new QLabel();
  HeaderLabel->setParent(this);
  HeaderLabel->move(20, 20);
  HeaderLabel->resize(760, 30);
  HeaderLabel->setText("Configuration");
  HeaderLabel->setAlignment(Qt::AlignLeft);
  HeaderLabel->setFont(QFont("Segoe UI", 17, QFont::Bold));

  //! Create label
  MessageArea = new QLabel();
  MessageArea->setParent(this);
  MessageArea->move(20, 320);
  MessageArea->resize(570, 20);
  MessageArea->setText("");
  MessageArea->setAlignment(Qt::AlignLeft);
  MessageArea->setFont(QFont("Segoe UI", 11, QFont::Normal));
  pal = MessageArea->palette();
  pal.setBrush(QPalette::WindowText, QBrush(MessageAreaTextColor));
  MessageArea->setPalette(pal);
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
ConfigurationDialog::SlotOKButtonPressed()
{
  QString                               dirName;
  QString                               databaseName;
  QString                               trackAVersion;
  QString                               trackBVersion;

  if ( ! VerifyInfo() ) {
    return;
  }
  dirName = InstallDirectoryNameEdit->text();
  databaseName = DatabaseNameEdit->text();
  trackAVersion = TrackASelectionCombo->currentText();
  trackBVersion = TrackBSelectionCombo->currentText();

  MainSystemSettings->SetInstallationInstallDirectory(dirName);
  MainSystemSettings->SetInstallationDatabaseName(databaseName);
  MainSystemSettings->SetTrackVersionsTrackAVersion(trackAVersion.toInt());
  MainSystemSettings->SetTrackVersionsTrackBVersion(trackBVersion.toInt());
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
ConfigurationDialog::SlotCancelButtonPressed()
{
  reject();
}

/*****************************************************************************!
 * Function : CreateInstallationFrame
 *****************************************************************************/
void
ConfigurationDialog::CreateInstallationFrame(void)
{
  InstallationFrame = new QGroupBox();
  InstallationFrame->setParent(this);
  InstallationFrame->resize(760,110);
  InstallationFrame->move(20,70);
  InstallationFrame->setTitle("Installation");
  InstallationFrame->setFont(QFont("Segoe UI", 11, QFont::Normal));

  InstallDirectoryLabel = new QLabel();  
  InstallDirectoryLabel->setParent(InstallationFrame);
  InstallDirectoryLabel->move(50,40);
  InstallDirectoryLabel->resize(130,20);
  InstallDirectoryLabel->setText("Install Directory");
  InstallDirectoryLabel->setAlignment(Qt::AlignRight);
  InstallDirectoryLabel->setFont(QFont("Segoe UI", 11, QFont::Normal));

  DatabaseNameLabel = new QLabel();
  DatabaseNameLabel->setParent(InstallationFrame);
  DatabaseNameLabel->move(50,70);
  DatabaseNameLabel->resize(130,20);
  DatabaseNameLabel->setText("Database Name");
  DatabaseNameLabel->setAlignment(Qt::AlignRight);
  DatabaseNameLabel->setFont(QFont("Segoe UI", 11, QFont::Normal));
  
    //! Create InstallDirectoryNameEdit LineEdit
  InstallDirectoryNameEdit = new QLineEdit();
  InstallDirectoryNameEdit->setParent(InstallationFrame);
  InstallDirectoryNameEdit->move(190,40);
  InstallDirectoryNameEdit->resize(510,20);
  InstallDirectoryNameEdit->setFont(QFont("Segoe UI", 10, QFont::Normal));
  
    //! Create DatabaseNameEdit LineEdit
  DatabaseNameEdit = new QLineEdit();
  DatabaseNameEdit->setParent(InstallationFrame);
  DatabaseNameEdit->move(190,70);
  DatabaseNameEdit->resize(510,20);
  DatabaseNameEdit->setFont(QFont("Segoe UI", 10, QFont::Normal));

  //! Create the InstallFilenameBrowseButton button
  InstallFilenameBrowseButton = new QPushButton();
  InstallFilenameBrowseButton->setParent(InstallationFrame);
  InstallFilenameBrowseButton->setIcon(QIcon(QPixmap(":/Images/Folder.png")));
  InstallFilenameBrowseButton->move(705, 36);
  InstallFilenameBrowseButton->resize(28, 28);
  InstallFilenameBrowseButton->setIconSize(QSize(28, 28));
  InstallFilenameBrowseButton->setFlat(true);
  connect(InstallFilenameBrowseButton, SIGNAL(pressed()), this, SLOT(SlotInstallFilenameBrowseButtonPushed()));

  //! Create the DatabaseNameBrowseButton button
  DatabaseNameBrowseButton = new QPushButton();
  DatabaseNameBrowseButton->setParent(InstallationFrame);
  DatabaseNameBrowseButton->move(705, 66);
  DatabaseNameBrowseButton->resize(28,28);
  DatabaseNameBrowseButton->setIcon(QIcon(QPixmap(":/Images/Folder.png")));
  DatabaseNameBrowseButton->setIconSize(QSize(28, 28));
  DatabaseNameBrowseButton->setFlat(true);
  connect(DatabaseNameBrowseButton, SIGNAL(pressed()), this, SLOT(SlotDatabaseNameBrowseButtonPushed()));
}

/*****************************************************************************!
 * Function : CreateTracksFrame
 *****************************************************************************/
void
ConfigurationDialog::CreateTracksFrame(void)
{
  TracksFrame = new QGroupBox();
  TracksFrame->setParent(this);
  TracksFrame->resize(760,110);
  TracksFrame->move(20,190);
  TracksFrame->setTitle("Tracks");
  TracksFrame->setFont(QFont("Segoe UI", 11, QFont::Normal));
                       
  TrackAVersionLabel = new QLabel();  
  TrackAVersionLabel->setParent(TracksFrame);
  TrackAVersionLabel->move(50,30);
  TrackAVersionLabel->resize(130,20);
  TrackAVersionLabel->setText("Track A Version");
  TrackAVersionLabel->setAlignment(Qt::AlignRight);

  TrackAVersionLabel->setFont(QFont("Segoe UI", 11, QFont::Normal));
  TrackBVersionLabel = new QLabel();
  TrackBVersionLabel->setParent(TracksFrame);
  TrackBVersionLabel->move(50,60);
  TrackBVersionLabel->resize(130,20);
  TrackBVersionLabel->setText("Track B Version");
  TrackBVersionLabel->setAlignment(Qt::AlignRight);
  TrackBVersionLabel->setFont(QFont("Segoe UI", 11, QFont::Normal));
  
    //! Create TrackASelectionCombo Combobox
  TrackASelectionCombo = new QComboBox();
  TrackASelectionCombo->setParent(TracksFrame);
  TrackASelectionCombo->move(190,30);
  TrackASelectionCombo->resize(190,20);
  TrackASelectionCombo->addItems(TrackSelectionComboAddItems());
  connect(TrackASelectionCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotTrackASelectionCombo_selected_item(int)));
  
    //! Create TrackBSelectionCombo Combobox
  TrackBSelectionCombo = new QComboBox();
  TrackBSelectionCombo->setParent(TracksFrame);
  TrackBSelectionCombo->move(190,70);
  TrackBSelectionCombo->resize(190,20);
  TrackBSelectionCombo->addItems(TrackSelectionComboAddItems());
  connect(TrackBSelectionCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotTrackBSelectionCombo_selected_item(int)));
}

/*****************************************************************************!
 * Function : TrackSelectionComboAddItems
 *****************************************************************************/
QStringList
ConfigurationDialog::TrackSelectionComboAddItems(void)
{
  QString                               st;
  QList<int>                            versions;
  QStringList                           returnVersions;
  
  versions = GetTrackVersions();
  returnVersions << QString("0");
  for ( auto i : versions ) {
    st = QString("%1").arg(i);
    returnVersions << st;
  }
  return returnVersions;
}

/*****************************************************************************!
 * Function : slotTrackASelectionCombo_selected_item
 *****************************************************************************/
void
ConfigurationDialog::slotTrackASelectionCombo_selected_item
(int in_selected_index)
{
  (void)in_selected_index;  
}

/*****************************************************************************!
 * Function : slotTrackBSelectionCombo_selected_item
 *****************************************************************************/
void
ConfigurationDialog::slotTrackBSelectionCombo_selected_item
(int in_selected_index)
{
  (void)in_selected_index;  
}

/*****************************************************************************!
 * Function : SlotInstallFilenameBrowseButtonPushed
 *****************************************************************************/
void
ConfigurationDialog::SlotInstallFilenameBrowseButtonPushed(void)
{
  QString                               dir;
  QString                               currentDir;

  currentDir = InstallDirectoryNameEdit->text();
  dir = QFileDialog::getExistingDirectory(this, tr("Installation Directory"),
                                          currentDir,
                                          QFileDialog::ShowDirsOnly
                                          | QFileDialog::DontResolveSymlinks);
  if ( dir.isEmpty() ) {
    return;
  }
  InstallDirectoryNameEdit->setText(dir);
}

/*****************************************************************************!
 * Function : InitializeValues
 *****************************************************************************/
void
ConfigurationDialog::InitializeValues(void)
{
  int                                   trackBVersion;
  int                                   trackAVersion;
  QString                               databaseName;
  QString                               dirName;

  MainSystemSettings->GetInstallationInstallDirectory(dirName);  
  InstallDirectoryNameEdit->setText(dirName);
  MainSystemSettings->GetInstallationDatabaseName(databaseName);  
  DatabaseNameEdit->setText(databaseName);

  MainSystemSettings->GetTrackVersionsTrackAVersion(trackAVersion);
  MainSystemSettings->GetTrackVersionsTrackBVersion(trackBVersion);
  TrackASelectionCombo->setCurrentText(QString("%1").arg(trackAVersion));
  TrackBSelectionCombo->setCurrentText(QString("%1").arg(trackBVersion));
}


/*****************************************************************************!
 * Function : SlotDatabaseNameBrowseButtonPushed
 *****************************************************************************/
void
ConfigurationDialog::SlotDatabaseNameBrowseButtonPushed(void)
{
  QString                               currentDir;
  QString                               filename;
  currentDir = InstallDirectoryNameEdit->text();

  filename = QFileDialog::getOpenFileName(this, tr("Database File Name"),
                                          currentDir,
                                          tr("Database Files (*.db);;All Files (*)"));
  if ( filename.isEmpty() ) {
    return;
  }
  DatabaseNameEdit->setText(filename);
}

/*****************************************************************************!
 * Function : VerifyInfo
 *****************************************************************************/
bool
ConfigurationDialog::VerifyInfo(void)
{
  QString                               trackAVersion;
  QString                               trackBVersion;
  QString                               installDir;
  QString                               databaseFilename;

  TRACE_FUNCTION_START();
  MessageArea->setText("Hi Mom");
  trackAVersion = TrackASelectionCombo->currentText();
  trackBVersion = TrackBSelectionCombo->currentText();

  installDir = InstallDirectoryNameEdit->text();
  databaseFilename = DatabaseNameEdit->text();
  TRACE_FUNCTION_QSTRING(installDir);
  TRACE_FUNCTION_QSTRING(databaseFilename);
  TRACE_FUNCTION_QSTRING(trackAVersion);
  TRACE_FUNCTION_QSTRING(trackBVersion);

  QFileInfo                             installInfo(installDir);
  if ( ! installInfo.exists() ) {
    MessageArea->setText(installDir + QString(" does not exist"));
    TRACE_FUNCTION_END();
    return false;
  }

  QFileInfo                             databaseInfo(databaseFilename);
  if ( ! databaseInfo.exists() ) {
    MessageArea->setText(databaseFilename + QString (" does not exist"));
    TRACE_FUNCTION_END();
    return false;
  }

  if ( trackAVersion == trackBVersion ) {
    MessageArea->setText(QString("The track versions can not be the same"));
    TRACE_FUNCTION_END();
    return false;
  }

  TRACE_FUNCTION_END();
  return true;
}
