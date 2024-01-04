/*****************************************************************************
 * FILE NAME    : main.h
 * DATE         : November 21 2023
 * PROJECT      : Signals Database
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _main_h_
#define _main_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QGuiApplication>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "sqlite3.h"
#include "MainConfig.h"
#include "TrackNumber.h"
#include "SystemSettings.h"

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
MainSetMainWindowGeometry
(QPoint InPosition, QSize InSize);

void
MainGetMainWindowGeometry
(QPoint &InPosition, QSize &InSize);

QList<int>
GetTrackVersions
();

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern
sqlite3*
MainDB;

extern
MainConfig*
MainConfiguration;

extern TrackNumber*
MainTrackAID;

extern TrackNumber*
MainTrackBID;

extern SystemSettings*
MainSystemSettings;

#endif /* _main_h_*/
