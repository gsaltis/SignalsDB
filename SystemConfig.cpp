/*****************************************************************************
 * FILE NAME    : SystemConfig.cpp
 * DATE         : November 21 2023
 * PROJECT      : Signals Database
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
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
#include "SystemConfig.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
QString SystemConfig::SystemName = "Signals Database";

/*****************************************************************************!
 * Function : SystemConfig
 *****************************************************************************/
SystemConfig::SystemConfig
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~SystemConfig
 *****************************************************************************/
SystemConfig::~SystemConfig
()
{
}

