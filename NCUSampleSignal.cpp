/*****************************************************************************
 * FILE NAME    : NCUSampleSignal.cpp
 * DATE         : November 20 2023
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
#include "NCUSampleSignal.h"

/*****************************************************************************!
 * Static Data
 *****************************************************************************/
QStringList
NCUSampleSignal::Tags = QStringList()
  << "SAMPLEName"
  << "Unit"
  << "SIndx"
  << "SChan"
  << "ValType"
  << "StorThreshold"
  << "StorInt"
  << "EvalExpRPN"
  << "EvalExpFull"
  << "Range"
  << "DisplayAttr"
  << "DisplayLvl"
  << "DisplayID"
  << "DispFmt"
  << "DispExpRPN"
  << "DispExpFull"
  << "Enums";
  
/*****************************************************************************!
 * Function : NCUSampleSignal
 *****************************************************************************/
NCUSampleSignal::NCUSampleSignal
() : NCUSignal()
{
  for ( auto tag : Tags ) {
    Values[tag] = QString();
  }
}

/*****************************************************************************!
 * Function : ~NCUSampleSignal
 *****************************************************************************/
NCUSampleSignal::~NCUSampleSignal
()
{
}


/*****************************************************************************!
 * Function : opeator==
 *****************************************************************************/
bool
NCUSampleSignal::Equal
(NCUSampleSignal* InSample)
{
  for ( auto tag : Tags ) {
    if ( Values[tag] != InSample->GetValue(tag) ) {
      return false;
    }
  }
  
  return true;
}

/*****************************************************************************!
 * Function : AddXCLRow
 *****************************************************************************/
void
NCUSampleSignal::AddXCLRow
(xlnt::worksheet* InWorkSheet, int InRow, int InStartingColumn, bool InBottomBorder)
{
  int                                   column;
  xlnt::border                          border;
  xlnt::border::border_property         borderProp;

  if ( InBottomBorder ) {
    borderProp.style(xlnt::border_style::medium);
    border.side(xlnt::border_side::bottom, borderProp);
  }
  column = InStartingColumn;

  class xlnt::cell ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue("SAMPLEName").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue("Unit").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "SIndx").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "SChan").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "ValType").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "StorThreshold").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "StorInt").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "EvalExpRPN").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "EvalExpFull").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "Range").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "DisplayAttr").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "DisplayLvl").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "DisplayID").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "DispFmt").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "DispExpRPN").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "DispExpFull").toStdString());
  ce.border(border);
  column++;
  
  ce = InWorkSheet->cell(column, InRow);
  ce.value(GetValue(  "Enums").toStdString());
  ce.border(border);
}
