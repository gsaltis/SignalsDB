/*****************************************************************************
 * FILE NAME    : XCLOptions.cpp
 * DATE         : December 14 2023
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
#include "XCLOptions.h"

/*****************************************************************************!
 * Function : XCLOptions
 *****************************************************************************/
XCLOptions::XCLOptions
() : QWidget()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ~XCLOptions
 *****************************************************************************/
XCLOptions::~XCLOptions
()
{
}

/*****************************************************************************!
 * Function : GetOption
 *****************************************************************************/
bool
XCLOptions::GetOption
(QString InOption)
{
  return Values[InOption];
}

/*****************************************************************************!
 * Function : SetOption
 *****************************************************************************/
void
XCLOptions::SetOption
(QString InOption, bool InValue)
{
  Values[InOption] = InValue;
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
XCLOptions::Initialize(void)
{
  Options << "SampleAll"
          << "SampleMajor"
          << "SampleMinor"
          << "SampleMissing2"
          << "SampleMissing3"
          << "SettingAll"
          << "SettingMajor"
          << "SettingMinor"
          << "SettingMissing2"
          << "SettingMissing3"
          << "AlarmAll"
          << "AlarmMajor"
          << "AlarmMinor"
          << "AlarmMissing2"
          << "AlarmMissing3"
          << "ControlAll"
          << "ControlMajor"
          << "ControlMinor"
          << "ControlMissing2"
          << "ControlMissing3"
          << "MinimalMajor"
          << "MinimalMinor";

  for ( auto option : Options ) {
    Values[option] = false;
  }
}
