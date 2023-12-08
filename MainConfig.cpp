/*****************************************************************************
 * FILE NAME    : MainConfig.cpp
 * DATE         : November 21 2023
 * PROJECT      : 
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
#include "MainConfig.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
sqlite3*
MainConfig::database = NULL;

EquipmentInformation*
MainConfig::equipmentInformation = NULL;

ControlInformation*
MainConfig::controlInformation = NULL;

AlarmInformation*
MainConfig::alarmInformation = NULL;

SettingInformation*
MainConfig::settingInformation = NULL;

SampleInformation*
MainConfig::sampleInformation = NULL;

/*****************************************************************************!
 * Function : MainConfig
 *****************************************************************************/
MainConfig::MainConfig
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~MainConfig
 *****************************************************************************/
MainConfig::~MainConfig
()
{
}

