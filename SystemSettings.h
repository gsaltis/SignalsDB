/*****************************************************************************
 * FILE NAME    : SystemSettings.h
 * DATE         : January 03 2024
 * PROJECT      : Signals Database
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _systemsettings_h_
#define _systemsettings_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QSettings>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SystemSettings
 *****************************************************************************/
class SystemSettings : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SystemSettings                ();

 //! Destructor
 public :
  ~SystemSettings               ();

 //! Public Methods
 public :
  void                          GetMainWindowPosition   (int& InX, int& InY);
  void                          GetMainWindowSize       (int& InWidth, int& InHeight);
  void                          SetMainWindowPosition   (int InX, int InY);
  void                          SetMainWindowSize       (int InWidth, int InHeight);
  void                          GetTrackVersionsTrackAVersion (int& InTrackAVersion);
  void                          SetTrackVersionsTrackAVersion (int InTrackAVersion);
  void                          GetTrackVersionsTrackBVersion (int& InTrackBVersion);
  void                          SetTrackVersionsTrackBVersion (int InTrackBVersion);
  void                          GetInstallationInstallDirectory (QString& InInstallDirectory);
  void                          SetInstallationInstallDirectory (QString InInstallDirectory);
  void                          GetInstallationDatabaseName (QString& InDatabaseName);
  void                          SetInstallationDatabaseName (QString InDatabaseName);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          VerifyMainWindowPosition (void);
  void                          VerifyMainWindowSize     (void);
  void                          VerifyTrackVersionsTrackAVersion ();
  void                          VerifyTrackVersionsTrackBVersion ();
  void                          VerifyInstallationInstallDirectory ();
  void                          VerifyInstallationDatabaseName ();

 //! Private Data
 private :
  QSettings*                    Settings;
  QString                       OrgName;
  QString                       AppName;

  QString                       MainWindowPositionXTag;
  QString                       MainWindowPositionYTag;
  QString                       MainWindowSizeWidthTag;
  QString                       MainWindowSizeHeightTag;

  int                           MainWindowPositionXDefault;
  int                           MainWindowPositionYDefault;
  int                           MainWindowSizeWidthDefault;
  int                           MainWindowSizeHeightDefault;
  int                           TrackAVersion;
  QString                       TrackVersionsTrackAVersionTag;
  QString                       TrackVersionsTrackAVersionDefault;
  int                           TrackBVersion;
  QString                       TrackVersionsTrackBVersionTag;
  QString                       TrackVersionsTrackBVersionDefault;
  QString                       InstallDirectory;
  QString                       InstallationInstallDirectoryTag;
  QString                       InstallationInstallDirectoryDefault;
  QString                       DatabaseName;
  QString                       InstallationDatabaseNameTag;
  QString                       InstallationDatabaseNameDefault;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _systemsettings_h_*/
