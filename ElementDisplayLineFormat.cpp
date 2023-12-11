/*****************************************************************************
 * FILE NAME    : ElementDisplayLineFormat.cpp
 * DATE         : December 08 2023
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
#include "ElementDisplayLineFormat.h"

/*****************************************************************************!
 * Function : ElementDisplayLineFormat
 *****************************************************************************/
ElementDisplayLineFormat::ElementDisplayLineFormat
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~ElementDisplayLineFormat
 *****************************************************************************/
ElementDisplayLineFormat::~ElementDisplayLineFormat
()
{
}

/*****************************************************************************!
 * Function : GetSignalTypeName
 *****************************************************************************/
QString
ElementDisplayLineFormat::GetSignalTypeName(void)
{
  return SignalTypeName;  
}

/*****************************************************************************!
 * Function : SetSignalTypeName
 *****************************************************************************/
void
ElementDisplayLineFormat::SetSignalTypeName
(QString InSignalTypeName)
{
  SignalTypeName = InSignalTypeName;  
}

/*****************************************************************************!
 * Function : GetLineOrder
 *****************************************************************************/
int
ElementDisplayLineFormat::GetLineOrder(void)
{
  return LineOrder;  
}

/*****************************************************************************!
 * Function : SetLineOrder
 *****************************************************************************/
void
ElementDisplayLineFormat::SetLineOrder
(int InLineOrder)
{
  LineOrder = InLineOrder;  
}

/*****************************************************************************!
 * Function : GetElementKey
 *****************************************************************************/
QString
ElementDisplayLineFormat::GetElementKey(void)
{
  return ElementKey;  
}

/*****************************************************************************!
 * Function : SetElementKey
 *****************************************************************************/
void
ElementDisplayLineFormat::SetElementKey
(QString InElementKey)
{
  ElementKey = InElementKey;  
}

/*****************************************************************************!
 * Function : GetElementName
 *****************************************************************************/
QString
ElementDisplayLineFormat::GetElementName(void)
{
  return ElementName;  
}

/*****************************************************************************!
 * Function : SetElementName
 *****************************************************************************/
void
ElementDisplayLineFormat::SetElementName
(QString InElementName)
{
  ElementName = InElementName;  
}

/*****************************************************************************!
 * Function : GetDifferenceSeverity
 *****************************************************************************/
QString
ElementDisplayLineFormat::GetDifferenceSeverity(void)
{
  return DifferenceSeverity;  
}

/*****************************************************************************!
 * Function : SetDifferenceSeverity
 *****************************************************************************/
void
ElementDisplayLineFormat::SetDifferenceSeverity
(QString InDifferenceSeverity)
{
  DifferenceSeverity = InDifferenceSeverity;  
}

/*****************************************************************************!
 * Function : GetLineHeightMultiplier
 *****************************************************************************/
int
ElementDisplayLineFormat::GetLineHeightMultiplier(void)
{
  return LineHeightMultiplier;  
}

/*****************************************************************************!
 * Function : SetLineHeightMultiplier
 *****************************************************************************/
void
ElementDisplayLineFormat::SetLineHeightMultiplier
(int InLineHeightMultiplier)
{
  LineHeightMultiplier = InLineHeightMultiplier;  
}
