/*****************************************************************************
 * FILE NAME    : ElementDisplayLineFormat.h
 * DATE         : December 08 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _elementdisplaylineformat_h_
#define _elementdisplaylineformat_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : ElementDisplayLineFormat
 *****************************************************************************/
class ElementDisplayLineFormat : public QWidget
{
  Q_OBJECT;

  //! Constructors
public :
  ElementDisplayLineFormat      ();

  //! Destructor
public :
  ~ElementDisplayLineFormat     ();

  //! Public Methods
public :
  QString                       GetSignalTypeName       (void);
  void                          SetSignalTypeName       (QString InSignalTypeName);
  int                           GetLineOrder            (void);
  void                          SetLineOrder            (int InLineOrder);
  QString                       GetElementKey           (void);
  void                          SetElementKey           (QString InElementKey);
  QString                       GetElementName          (void);
  void                          SetElementName          (QString InElementName);
  QString                       GetDifferenceSeverity   (void);
  void                          SetDifferenceSeverity   (QString InDifferenceSeverity);
  int                           GetLineHeightMultiplier (void);
  void                          SetLineHeightMultiplier (int InLineHeightMultiplier);

  //! Public Data
public :

  //! Protected Methods
protected :

  //! Protected Data
protected :

  //! Private Methods
private :

  //! Private Data
private :
  QString                       SignalTypeName;
  int                           LineOrder;
  QString                       ElementKey;
  QString                       ElementName;
  QString                       DifferenceSeverity;
  int                           LineHeightMultiplier;

  //! Public Slots
public slots :

  //! Public Signals
signals :

  //! Public Actions
public :

};

#endif /* _elementdisplaylineformat_h_*/
