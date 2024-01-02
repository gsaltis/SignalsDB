/*****************************************************************************
 * FILE NAME    : XCLOptions.h
 * DATE         : December 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _xcloptions_h_
#define _xcloptions_h_

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
 * Exported Class : XCLOptions
 *****************************************************************************/
class XCLOptions : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  XCLOptions                    ();

 //! Destructor
 public :
  ~XCLOptions                   ();

 //! Public Methods
 public :
  bool                          GetOption               (QString InOption);
  void                          SetOption               (QString InOption, bool InValue);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);

 //! Private Data
 private :
  QStringList                   Options;
  QHash<QString, bool>          Values;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _xcloptions_h_*/
