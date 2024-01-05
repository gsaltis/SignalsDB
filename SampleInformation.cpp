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
                         "Track,"                       // 0
                         "Eq,"                          // 1
                         "SID,"                         // 2
                         "SampleName,"                  // 3
                         "ResourceID,"                  // 4
                         "Unit,"                        // 5
                         "SamplerIndex,"                // 6
                         "SamplerChannel,"              // 7
                         "ValueType,"                   // 8
                         "StoringThreshold,"            // 9
                         "StoringInterval,"             // 10
                         "EvalExprRPN,"                 // 11
                         "EvalExprFull,"                // 12
                         "Range,"                       // 13
                         "DisplayAttr,"                 // 14
                         "DisplayLevel,"                // 15
                         "DisplayID,"                   // 16
                         "DisplayFormat,"               // 17
                         "DisplayExprRPN,"              // 18
                         "DisplayExprFull,"             // 19
                         "Enums "                       // 20
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
        sample->SetValue("SampleName", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("ResourceID", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("Unit", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("SamplerIndex", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("SamplerChannel", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("ValueType", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("StoringThreshold", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("StoringInterval", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("EvalExprRPN", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("EvalExprFull", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("Range", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayAttr", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayLevel", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayID", 		QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayFormat", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayExprRPN", 	QString((char*)sqlite3_column_text(statement, i++)));
        sample->SetValue("DisplayExprFull", 	QString((char*)sqlite3_column_text(statement, i++)));
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
    if ( e->Track != MainTrackAID->GetNumber() ) {
      continue;
    }

    samplePair = new SampleSignalPair(e->ID, e->Type, e, NULL);
    samplePairs << samplePair;
  }

  for ( i = 0; i < n; i++ ){
    e = samples[i];
    if ( e->Track != MainTrackBID->GetNumber() ) {
      continue;
    }
    samplePair = FindPairByID(e->ID, e->Type);
    if ( NULL == samplePair ) {
      samplePair = new SampleSignalPair(e->ID, e->Type, NULL, e);
      samplePairs << samplePair;
      continue;
    }
    samplePair->AddTrackBSignal(e);
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
 * Function : GetTrackACount
 *****************************************************************************/
int
SampleInformation::GetTrackACount(void)
{
  return GetTrackCount(MainTrackAID->GetNumber());
}

/*****************************************************************************!
 * Function : GetTrackBCount
 *****************************************************************************/
int
SampleInformation::GetTrackBCount(void)
{
  return GetTrackCount(MainTrackBID->GetNumber());
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
 * Function : GetTrackAMissingCount
 *****************************************************************************/
int
SampleInformation::GetTrackAMissingCount(void)
{
  SampleSignalPair*                     ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    ep = samplePairs[i];
    if ( ep->GetTrackA() == NULL ) {
      count++;
    }
  }
  return count;  
}

/*****************************************************************************!
 * Function : GetTrackBMissingCount
 *****************************************************************************/
int
SampleInformation::GetTrackBMissingCount(void)
{
  SampleSignalPair*                     ep;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = samplePairs.size();
  for (i = 0; i < n; i++) {
    ep = samplePairs[i];
    if ( ep->GetTrackB() == NULL ) {
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

/*****************************************************************************!
 * Function : AddAllWorksheet
 *****************************************************************************/
void
SampleInformation::AddAllWorksheet
(xlnt::workbook* InWorkbook)
{
  int                                   row;
  xlnt::worksheet                       ws;

  ws = InWorkbook->create_sheet();
  ws.title("Samples All");

  AddXCLHeaders(&ws);
  row = 2;
  for ( auto pair : samplePairs ) {
    row = pair->AddXCLFullRows(&ws, row);
  }
}

/*****************************************************************************!
 * Function : AddMajorDifferWorksheet
 *****************************************************************************/
void
SampleInformation::AddMajorDifferWorksheet
(xlnt::workbook* InWorkbook)
{
  int                                   row;
  xlnt::worksheet                       ws;
  xlnt::font                            font;

  ws = InWorkbook->create_sheet();
  ws.title("Samples Major Differs");

  AddXCLHeaders(&ws);
  
 
  row = 2;
  for ( auto pair : samplePairs ) {
    row = pair->AddXCLMajorDifferRows(&ws, row);
  }
}

/*****************************************************************************!
 * Function : AddMinorDifferWorksheet
 *****************************************************************************/
void
SampleInformation::AddMinorDifferWorksheet
(xlnt::workbook* InWorkbook)
{
  int                                   row;
  xlnt::worksheet                       ws;
  xlnt::font                            font;

  font.bold(true);
  font.name("Liberation Sans");
  ws = InWorkbook->create_sheet();
  ws.title("Samples All");

  xlnt::cell  ce = ws.cell(1, 1);
  ce.font(font);
  ce.value("Equipment ID");
  
  row = 2;
  for ( auto pair : samplePairs ) {
    row = pair->AddXCLFullRows(&ws, row);
  }
}

/*****************************************************************************!
 * Function : AddTrackAOnlyWorksheet
 *****************************************************************************/
void
SampleInformation::AddTrackAOnlyWorksheet
(xlnt::workbook* InWorkbook)
{
  int                                   row;
  xlnt::worksheet                       ws;
  xlnt::font                            font;

  font.bold(true);
  font.name("Liberation Sans");
  ws = InWorkbook->create_sheet();
  ws.title("Samples All");

  xlnt::cell  ce = ws.cell(1, 1);
  ce.font(font);
  ce.value("Equipment ID");
  
  row = 2;
  for ( auto pair : samplePairs ) {
    row = pair->AddXCLFullRows(&ws, row);
  }
}

/*****************************************************************************!
 * Function : AddTrackBOnlyWorksheet
 *****************************************************************************/
void
SampleInformation::AddTrackBOnlyWorksheet
(xlnt::workbook* InWorkbook)
{
  int                                   row;
  xlnt::worksheet                       ws;

  ws = InWorkbook->create_sheet();
  ws.title("Samples All");

  row = 2;
  for ( auto pair : samplePairs ) {
    row = pair->AddXCLFullRows(&ws, row);
  }
}

/*****************************************************************************!
 * Function : AddXCLHeaders
 *****************************************************************************/
void
SampleInformation::AddXCLHeaders
(xlnt::worksheet* InWorkSheet)
{
  int                                   n;
  QStringList                           headerNames;
  xlnt::font                            font;
  int                                   column;

  headerNames
    << "Equipment ID"
    << "Signal ID"
    << "Name"
    << "Unit"
    << "Signal Index"
    << "Signal Channel"
    << "Value Type"
    << "Store Threshold"
    << "Store Int"
    << "Eval Expression RPN"
    << "Eval Expression Full"
    << "Range"
    << "Display Attribute"
    << "Display Level"
    << "Display ID"
    << "Display Format"
    << "Display Expression RPN"
    << "Display Expression Full"
    << "Enums";
  

  font.bold(true);
  font.name("Liberation Sans");

  n = headerNames.size();
  for (column = 0; column < n; column++) {
    xlnt::cell  ce = InWorkSheet->cell(column + 1, 1);
    ce.font(font);
    ce.value(headerNames[column].toStdString());
  }
}
