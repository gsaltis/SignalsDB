/*****************************************************************************
 * FILE NAME    : SystemSettings.cpp
 * DATE         : January 03 2024
 * PROJECT      : Signals Database
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SystemSettings.h"

/*****************************************************************************!
 * Function : GetTrackVersionsTrackBVersion
 *****************************************************************************/
void
SystemSettings::GetTrackVersionsTrackBVersion
(int& InTrackBVersion)
{
  VerifyTrackVersionsTrackBVersion();
  InTrackBVersion = Settings->value(TrackVersionsTrackBVersionTag).toInt();
}
  

/*****************************************************************************!
 * Function : SystemSettings
 *****************************************************************************/
SystemSettings::SystemSettings
() : QWidget()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~SystemSettings
 *****************************************************************************/
SystemSettings::~SystemSettings
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
SystemSettings::Initialize()
{
  OrgName = "Vertiv";  
  AppName = "SignalsDB";
  Settings = new QSettings(OrgName, AppName);

  MainWindowPositionXTag        = "MainWindow/X";
  MainWindowPositionYTag        = "MainWindow/Y";
  MainWindowSizeWidthTag        = "MainWindow/Width";
  MainWindowSizeHeightTag       = "MainWindow/Height";

  MainWindowPositionXDefault    = 10;
  MainWindowPositionYDefault    = 10;
  MainWindowSizeWidthDefault    = 1000;
  MainWindowSizeHeightDefault   = 800;
  TrackVersionsTrackAVersionTag = "TrackVersions/TrackAVersion";
  TrackVersionsTrackAVersionDefault = 0;
  TrackVersionsTrackBVersionTag = "TrackVersions/TrackBVersion";
  TrackVersionsTrackBVersionDefault = 0;
  InstallationInstallDirectoryTag = "Installation/InstallDirectory";
  InstallationInstallDirectoryDefault = "D:/Source/SignalsDB/";
  InstallationDatabaseNameTag = "Installation/DatabaseName";
  InstallationDatabaseNameDefault = QString("Signals.db");
}

/*****************************************************************************!
 * Function : GetMainWindowPosition
 *****************************************************************************/
void
SystemSettings::GetMainWindowPosition
(int& InX, int& InY)
{
  VerifyMainWindowPosition();
  InX = Settings->value(MainWindowPositionXTag).toInt();
  InY = Settings->value(MainWindowPositionYTag).toInt();
}

/*****************************************************************************!
 * Function : VerifyMainWindowPosition
 *****************************************************************************/
void
SystemSettings::VerifyMainWindowPosition(void)
{
  if ( ! Settings->contains(MainWindowPositionXTag) ) {
    Settings->setValue(MainWindowPositionXTag, MainWindowPositionXDefault);
  }
  if ( ! Settings->contains(MainWindowPositionYTag) ) {
    Settings->setValue(MainWindowPositionYTag, MainWindowPositionYDefault);
  }
}

/*****************************************************************************!
 * Function : GetMainWindowSize
 *****************************************************************************/
void
SystemSettings::GetMainWindowSize
(int& InWidth, int& InHeight)
{
  VerifyMainWindowSize();
  InWidth = Settings->value(MainWindowSizeWidthTag).toInt();
  InHeight = Settings->value(MainWindowSizeHeightTag).toInt();
}

/*****************************************************************************!
 * Function : VerifyMainWindowSize
 *****************************************************************************/
void
SystemSettings::VerifyMainWindowSize(void)
{
  if ( ! Settings->contains(MainWindowSizeWidthTag) ) {
    Settings->setValue(MainWindowSizeWidthTag, MainWindowSizeWidthDefault);
  }
  if ( ! Settings->contains(MainWindowSizeHeightTag) ) {
    Settings->setValue(MainWindowSizeHeightTag, MainWindowSizeHeightDefault);
  }
}

/*****************************************************************************!
 * Function : SetMainWindowPosition
 *****************************************************************************/
void
SystemSettings::SetMainWindowPosition
(int InX, int InY)
{
  Settings->setValue(MainWindowPositionXTag, InX);
  Settings->setValue(MainWindowPositionYTag, InY);
}

/*****************************************************************************!
 * Function : SetMainWindowSize
 *****************************************************************************/
void
SystemSettings::SetMainWindowSize
(int InWidth, int InHeight)
{
  Settings->setValue(MainWindowSizeWidthTag, InWidth);
  Settings->setValue(MainWindowSizeHeightTag, InHeight);
}

/*****************************************************************************!
 * Function : GetTrackVersionsTrackAVersion
 *****************************************************************************/
void
SystemSettings::GetTrackVersionsTrackAVersion
(int& InTrackAVersion)
{
  VerifyTrackVersionsTrackAVersion();  
  InTrackAVersion = Settings->value(TrackVersionsTrackAVersionTag).toInt();
}

/*****************************************************************************!
 * Function : VerifyTrackVersionsTrackAVersion
 *****************************************************************************/
void
SystemSettings::VerifyTrackVersionsTrackAVersion()
{
  if ( ! Settings->contains(TrackVersionsTrackAVersionTag) ) {  
    Settings->setValue(TrackVersionsTrackAVersionTag, TrackVersionsTrackAVersionDefault);
  }
}

/*****************************************************************************!
 * Function : SetTrackVersionsTrackAVersion
 *****************************************************************************/
void
SystemSettings::SetTrackVersionsTrackAVersion
(int InTrackAVersion)
{
  Settings->setValue(TrackVersionsTrackAVersionTag, InTrackAVersion);  
}

/*****************************************************************************!
 * Function : VerifyTrackVersionsTrackBVersion
 *****************************************************************************/
void
SystemSettings::VerifyTrackVersionsTrackBVersion()
{
  if ( ! Settings->contains(TrackVersionsTrackBVersionTag) ) {  
    Settings->setValue(TrackVersionsTrackBVersionTag, TrackVersionsTrackBVersionDefault);
  }
}

/*****************************************************************************!
 * Function : SetTrackVersionsTrackBVersion
 *****************************************************************************/
void
SystemSettings::SetTrackVersionsTrackBVersion
(int InTrackBVersion)
{
  Settings->setValue(TrackVersionsTrackBVersionTag, InTrackBVersion);  
}

/*****************************************************************************!
 * Function : GetInstallationInstallDirectory
 *****************************************************************************/
void
SystemSettings::GetInstallationInstallDirectory
(QString& InInstallDirectory)
{
  VerifyInstallationInstallDirectory();
  InInstallDirectory = Settings->value(InstallationInstallDirectoryTag).toString();
}

/*****************************************************************************!
 * Function : VerifyInstallationInstallDirectory
 *****************************************************************************/
void
SystemSettings::VerifyInstallationInstallDirectory()
{
  if ( ! Settings->contains(InstallationInstallDirectoryTag) ) {  
    Settings->setValue(InstallationInstallDirectoryTag, InstallationInstallDirectoryDefault);
  }
}

/*****************************************************************************!
 * Function : SetInstallationInstallDirectory
 *****************************************************************************/
void
SystemSettings::SetInstallationInstallDirectory
(QString InInstallDirectory)
{  
  Settings->setValue(InstallationInstallDirectoryTag, InInstallDirectory);
}

/*****************************************************************************!
 * Function : GetInstallationDatabaseName
 *****************************************************************************/
void
SystemSettings::GetInstallationDatabaseName
(QString& InDatabaseName)
{
  VerifyInstallationDatabaseName();  
  InDatabaseName = Settings->value(InstallationDatabaseNameTag).toString();
}

/*****************************************************************************!
 * Function : VerifyInstallationDatabaseName
 *****************************************************************************/
void
SystemSettings::VerifyInstallationDatabaseName()
{
  if ( ! Settings->contains(InstallationDatabaseNameTag) ) {  
    Settings->setValue(InstallationDatabaseNameTag, InstallationDatabaseNameDefault);
  }
}

/*****************************************************************************!
 * Function : SetInstallationDatabaseName
 *****************************************************************************/
void
SystemSettings::SetInstallationDatabaseName
(QString InDatabaseName)
{
  Settings->setValue(InstallationDatabaseNameTag, InDatabaseName);
}
