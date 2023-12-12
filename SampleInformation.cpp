/*****************************************************************************
 * FILE NAME    : SampleInformation.cpp
 * DATE         : November 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMessageBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SampleInformation.h"
#include "MainConfig.h"
#include "main.h"

/*****************************************************************************!
 * Function : SampleInformation
 *****************************************************************************/
SampleInformation::SampleInformation
() : SignalsInformation()
{
}

/*****************************************************************************!
 * Function : ~SampleInformation
 *****************************************************************************/
SampleInformation::~SampleInformation
()
{
}

/*****************************************************************************!
 * Function : AddSample
 *****************************************************************************/
void
SampleInformation::AddSample
(NCUSampleSignal* InSample)
{
  if ( NULL == InSample ) {
    return;
  }
  samples << InSample;
}

/*****************************************************************************!
 * Function : FindSampleByID
 *****************************************************************************/
NCUSampleSignal*
SampleInformation::FindSampleByID
(int InTrack, int InID)
{
  for ( auto i : samples ) {
    if ( i->GetTrack() == InTrack && i->GetID() == InID ) {
      return i;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : SQLRead
 *****************************************************************************/
void
SampleInformation::SQLRead
(sqlite3* InDatabase)
{
  NCUSampleSignal*                      sample;
  bool                                  finished;
  int                                   n;
  sqlite3_stmt*                         statement;
  QString                               sqlStatement;
  QString                               s;
  int                                   i;
  
  sqlStatement = QString("SELECT "
                         "Track,"               // 0
                         "Eq,"                  // 1
                         "SID,"                 // 2
                         "SAMPLEName,"          // 3
                         "Unit,"                // 4
                         "SIndx,"               // 5
                         "SChan,"               // 6
                         "ValType,"             // 7
                         "StorThreshold,"       // 8
                         "StorInt,"             // 9
                         "EvalExpRPN,"          // 10
                         "EvalExpFull,"         // 11
                         "Range,"               // 12
                         "DisplayAttr,"         // 13
                         "DisplayLvl,"          // 14
                         "DisplayID,"           // 15
                         "DispFmt,"             // 16
                         "DispExpRPN,"          // 17
                         "DispExpFull,"         // 18
                         "Enums "               // 19
                         "FROM Sample ORDER by CAST(Eq AS INTEGER), CAST(SID AS INTEGER), Track;");

  n = sqlite3_prepare_v2(InDatabase, sqlStatement.toStdString().c_str(), sqlStatement.length(), &statement, NULL);
  if ( n != SQLITE_OK ) {

    QMessageBox box = QMessageBox(QMessageBox::Critical,
                                  "sqlite3_prepare_v2 Fail",
                                  QString("sqlite3_prepare_v2() FAIL\n"
                                          "%1 : %2\n"
                                          "%3\n"
                                          "%4")
                                  .arg(__FILE__).arg(__LINE__)
                                  .arg(sqlStatement)
                                  .arg(sqlite3_errstr(n)));
    box.exec();
    exit(EXIT_FAILURE);
  }

  //!
  finished = false;
  while ( ! finished ) {
    n = sqlite3_step(statement);
    switch (n) {
      case SQLITE_BUSY : {
        break;
      }
      
      case SQLITE_DONE : {
        finished = true;
        break;
      }
      
      case SQLITE_ROW : {
        sample = new NCUSampleSignal();
        sample->SetTrack(sqlite3_column_int(statement, 0));

        s = QString((char*)sqlite3_column_text(statement, 1));
        sample->SetID(s.toInt());
        
        s = QString((char*)sqlite3_column_text(statement, 2));
        sample->SetType(s.toInt());

        //!
        i = 3;
        sample->SetValue("SAMPLEName", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("Unit", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("SIndx", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("SChan", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("ValType", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("StorThreshold", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("StorInt", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("EvalExpRPN", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("EvalExpFull", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("Range", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayAttr", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayLvl", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayID", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DispFmt", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DispExpRPN", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DispExpFull", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("Enums", 		QString((char*)sqlite3_column_text(statement, i++)));
        samples << sample;
        break;
      }
      
      case SQLITE_ERROR : {
        break;
      }
      
      case SQLITE_MISUSE : {
        break;
      }
    }

  };

  sqlite3_finalize(statement);
  CreatePairs();
}

/*****************************************************************************!
 * Function : GetCountByTrack
 *****************************************************************************/
int
SampleInformation::GetCountByTrack
(int InTrack)
{
  int                                   n;

  n = 0;

  for ( auto i : samples ) {
    if ( i->GetTrack() == InTrack ) {
      n++;
    }
  }
  return n;
}

/*****************************************************************************!
 * Function : CreatePairs
 *****************************************************************************/
void
SampleInformation::CreatePairs(void)
{
  SampleSignalPair*                     samplePair;
  NCUSampleSignal*                      e;
  int                                   i;
  int                                   n;

  n = samples.size();
  for (i = 0; i < n; i++) {
    e = samples[i];
    if ( e->Track != 2 ) {
      continue;
    }

    samplePair = new SampleSignalPair(e->ID, e->Type, e, NULL);
    samplePairs << samplePair;
  }

  for ( i = 0; i < n; i++ ){
    e = samples[i];
    if ( e->Track != 3 ) {
      continue;
    }
    samplePair = FindPairByID(e->ID, e->Type);
    if ( NULL == samplePair ) {
      samplePair = new SampleSignalPair(e->ID, e->Type, NULL, e);
      samplePairs << samplePair;
      continue;
    }
    samplePair->AddTrack3Signal(e);
  }
}

/*****************************************************************************!
 * Function : FindPairByID
 *****************************************************************************/
SampleSignalPair*
SampleInformation::FindPairByID
(int InID, int InSID)
{
  int                                   i, n;
  SampleSignalPair*                     pair;

  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    pair = samplePairs[i];
    if ( pair->GetID() == InID && pair->GetSID() == InSID ) {
      return pair;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetTrack2Count
 *****************************************************************************/
int
SampleInformation::GetTrack2Count(void)
{
  return GetTrackCount(2);
}

/*****************************************************************************!
 * Function : GetTrack3Count
 *****************************************************************************/
int
SampleInformation::GetTrack3Count(void)
{
  return GetTrackCount(3);
}

/*****************************************************************************!
 * Function : GetTrackCount
 *****************************************************************************/
int
SampleInformation::GetTrackCount
(int InTrack)
{
  int                                   count;
  int                                   i;
  int                                   n;
  NCUSampleSignal*                      e;

  count = 0;
  n = samples.size();
  for (i = 0; i < n; i++) {
    e = samples[i];

    if ( e->Track == InTrack ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetTrack2MissingCount
 *****************************************************************************/
int
SampleInformation::GetTrack2MissingCount(void)
{
  SampleSignalPair*                     ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    ep = samplePairs[i];
    if ( ep->GetTrack2() == NULL ) {
      count++;
    }
  }
  return count;  
}

/*****************************************************************************!
 * Function : GetTrack3MissingCount
 *****************************************************************************/
int
SampleInformation::GetTrack3MissingCount(void)
{
  SampleSignalPair*                     ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    ep = samplePairs[i];
    if ( ep->GetTrack3() == NULL ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetTrackDifferCount
 *****************************************************************************/
int
SampleInformation::GetTrackDifferCount(void)
{
  SampleSignalPair*                     ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    ep = samplePairs[i];
    if ( ep->Differ() ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetPairByIndex
 *****************************************************************************/
SampleSignalPair*
SampleInformation::GetPairByIndex
(int InIndex)
{
  if ( InIndex >= samplePairs.size() ) {
    return NULL;
  }
  return samplePairs[InIndex];
}

/*****************************************************************************!
 * Function : GetPairCount
 *****************************************************************************/
int
SampleInformation::GetPairCount
()
{
  return samplePairs.size();
}

/*****************************************************************************!
 * Function : GetTrackDifferCount
 *****************************************************************************/
void
SampleInformation::GetTrackDifferCount
(int &InSignalMajorCount, int &InMajorCount, int &InSignalMinorCount, int &InMinorCount)
{
  int                                   pairMinor;
  int                                   pairMajor;
  SampleSignalPair*                    ep;
  int                                   i;
  int                                   n;
  QList<ElementDisplayLineFormat*>      formats;
  int                                   signalMajor;
  int                                   signalMinor;

  signalMajor = 0;
  signalMinor = 0;
  InMajorCount = 0;
  InMinorCount = 0;
  formats = MainConfiguration->GetElementLineFormats("Samples");

  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    ep = samplePairs[i];
    pairMajor = 0;
    pairMinor = 0;
    ep->GetDifferCounts(pairMajor, pairMinor, formats);
    if ( pairMajor > 0 ) {
      signalMajor++;
    }
    if ( pairMinor > 0 ) {
      signalMinor++;
    }
    InMajorCount += pairMajor;
    InMinorCount += pairMinor;
  }
  InSignalMajorCount = signalMajor;
  InSignalMinorCount = signalMinor;
}

