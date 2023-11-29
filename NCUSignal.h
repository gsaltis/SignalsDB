/*****************************************************************************
 * FILE NAME    : NCUSignal.h
 * DATE         : November 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _ncusignal_h_
#define _ncusignal_h_

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
 * Exported Class : NCUSignal
 *****************************************************************************/
class NCUSignal : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  NCUSignal                     ();

 //! Destructor
 public :
  ~NCUSignal                    ();

 //! Public Methods
 public :
  int                           GetTrack                (void);
  void                          SetTrack                (int InTrack);
  int                           GetID                   (void);
  void                          SetID                   (int InID);
  int                           GetType                 (void);
  void                          SetType                 (int InType);
  QString                       GetName                 (void);
  void                          SetName                 (QString InName);
  QString                       GetIDName               (void);
  void                          SetIDName               (QString InIDName);

 //! Public Data
 public :
  int                           Track;
  int                           ID;
  int                           Type;
  QString                       Name;
  QString                       IDName; 

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _ncusignal_h_*/
