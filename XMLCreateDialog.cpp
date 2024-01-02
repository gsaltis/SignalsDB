/*****************************************************************************
 * FILE NAME    : XMLCreateDialog.cpp
 * DATE         : December 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "XMLCreateDialog.h"

/*****************************************************************************!
 * Function : XMLCreateDialog
 *****************************************************************************/
XMLCreateDialog::XMLCreateDialog
(XCLOptions* InOptions) : QDialog()
{
  TopPaneHeight = 70;
  Options = InOptions;
  
  Initialize();
}

/*****************************************************************************!
 * Function : ~XMLCreateDialog
 *****************************************************************************/
XMLCreateDialog::~XMLCreateDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
XMLCreateDialog::Initialize(void)
{
  CreateSubWindows();  
  CreateConnections();
  resize(XMLCREATE_DIALOG_WIDTH, XMLCREATE_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
XMLCreateDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
XMLCreateDialog::CreateSubWindows(void)
{
  int                                   checkBoxH;
  int                                   checkBoxW;
  int                                   n;
  int                                   w;
  int                                   x;
  int                                   y;
  QPalette                              pal;
  int                                   buttonHeight;
  int                                   buttonGap;
  int                                   cancelButtonX;
  int                                   okButtonX;
  int                                   buttonY;
  int                                   cancelButtonWidth;
  int                                   okButtonWidth;
  QLabel*                               label;
  QFont                                 labelFont = QFont("Segoe UI", 10, QFont::Bold);
  int                                   leftLabelWidth = 120;
  int                                   leftLabelHeight = 20;
  int                                   leftLabelY = 10;
  int                                   leftLabelX = 0;
  int                                   verticalGap = 5;
  int                                   ys[7];
  int                                   xs[5];

  checkBoxW = 20;
  checkBoxH = 20;
  okButtonWidth = 40;
  cancelButtonWidth = 60;
  buttonGap = 5;
  buttonHeight = 20;
  okButtonX = XMLCREATE_DIALOG_WIDTH - (okButtonWidth + cancelButtonWidth + (2 * buttonGap));
  cancelButtonX = XMLCREATE_DIALOG_WIDTH - (cancelButtonWidth + buttonGap);
  buttonY = XMLCREATE_DIALOG_HEIGHT - (buttonGap + buttonHeight);
 
  OKButton = new QPushButton();
  OKButton->setParent(this);
  OKButton->setText("OK");
  OKButton->move(okButtonX, buttonY);
  OKButton->resize(okButtonWidth, buttonHeight);
  
  CancelButton = new QPushButton();
  CancelButton->setParent(this);
  CancelButton->setText("Cancel");
  CancelButton->move(cancelButtonX, buttonY);
  CancelButton->resize(cancelButtonWidth, buttonHeight);

  LeftPane = new QWidget();
  LeftPane->setParent(this);

  pal = LeftPane->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(208, 208, 208)));
  LeftPane->setPalette(pal);
  LeftPane->setAutoFillBackground(true);

  TopPane = new QWidget();
  TopPane->setParent(this);
  pal = TopPane->palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(208, 208, 208)));
  TopPane->setPalette(pal);
  TopPane->setAutoFillBackground(true);

  //!
  label = new QLabel();
  label->setParent(TopPane);
  label->move(120, 10);
  label->resize(350, 30);
  label->setFont(QFont("Segoe UI", 18, QFont::Bold));
  label->setText("Create Excel Spreadsheets");

  n = 0;
  x = 135;
  xs[n] = x;
  n++;
  
  y = TopPaneHeight - 20;
  w = 60;
  label = new QLabel("All", TopPane);
  label->setGeometry(x, y, w, 20);
  label->setAlignment(Qt::AlignLeft);
  label->setFont(labelFont);
  x += w + 5;
  xs[n] = x;
  n++;

  w = 80;
  label = new QLabel("Major Diffs", TopPane);
  label->setGeometry(x, y, w, 20);
  label->setAlignment(Qt::AlignLeft);
  label->setFont(labelFont);
  x += w + 5;
  xs[n] = x;
  n++;
  
  label = new QLabel("Minor Diffs", TopPane);
  label->setGeometry(x, y, w, 20);
  label->setAlignment(Qt::AlignLeft);
  label->setFont(labelFont);
  x += w + 10;
  w = 100;
  xs[n] = x;
  n++;
  
  label = new QLabel("Track2 Missing", TopPane);
  label->setGeometry(x, y, w, 20);
  label->setAlignment(Qt::AlignLeft);
  label->setFont(labelFont);
  x += w + 5;
  xs[n] = x;
  n++;
  
  label = new QLabel("Track3 Missing", TopPane);
  label->setGeometry(x, y, w, 20);
  label->setAlignment(Qt::AlignLeft);
  label->setFont(labelFont);

  n = 0;
  //!
  y = leftLabelY;
  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("EQUIPMENT : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y + TopPaneHeight;
  n++;
  y += (leftLabelHeight + verticalGap);
  
  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("SETTING : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y  + TopPaneHeight;
  n++;
  y += (leftLabelHeight + verticalGap);

  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("SAMPLE : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y + TopPaneHeight;
  n++;
  y += (leftLabelHeight + verticalGap);

  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("CONTROL : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y + TopPaneHeight;
  n++;
  y += (leftLabelHeight + verticalGap);

  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("ALARM : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y + TopPaneHeight;
  n++;
  y += ((leftLabelHeight * 2) + verticalGap);

  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("MINIMAL : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y + TopPaneHeight;
  n++;
  y += ((leftLabelHeight * 2) + verticalGap);

  label = new QLabel();
  label->setParent(LeftPane);
  label->move(leftLabelX, y);
  label->setFont(labelFont);
  label->setText("FILE NAME : ");
  label->setAlignment(Qt::AlignRight);
  label->resize(leftLabelWidth, leftLabelHeight);
  ys[n] = y  + TopPaneHeight;

  FileNameEdit = new QLineEdit(this);
  FileNameEdit->setGeometry(xs[0], ys[6], size().width() - (xs[0] * 2), 20);
  //!
  SampleAllCB = new QCheckBox(this);
  SampleAllCB->setGeometry(xs[0], ys[2], checkBoxW, checkBoxH);
  SampleAllCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SampleAll"] = SampleAllCB;
  
  SampleMajorCB = new QCheckBox(this);
  SampleMajorCB->setGeometry(xs[1], ys[2], checkBoxW, checkBoxH);
  SampleMajorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SampleMajor"] = SampleMajorCB;
  
  SampleMinorCB = new QCheckBox(this);
  SampleMinorCB->setGeometry(xs[2], ys[2], checkBoxW, checkBoxH);
  SampleMinorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SampleMinor"] = SampleMinorCB;
  
  SampleMissing2CB = new QCheckBox(this);
  SampleMissing2CB->setGeometry(xs[3], ys[2], checkBoxW, checkBoxH);
  SampleMissing2CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SampleMissing2"] = SampleMissing2CB;
  
  SampleMissing3CB = new QCheckBox(this);
  SampleMissing3CB->setGeometry(xs[4], ys[2], checkBoxW, checkBoxH);
  SampleMissing3CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SampleMissing3"] = SampleMissing3CB;
  
  //!
  EquipmentAllCB = new QCheckBox(this);
  EquipmentAllCB->setGeometry(xs[0], ys[0], checkBoxW, checkBoxH);
  EquipmentAllCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["EquipmentAll"] = EquipmentAllCB;
  
  EquipmentMajorCB = new QCheckBox(this);
  EquipmentMajorCB->setGeometry(xs[1], ys[0], checkBoxW, checkBoxH);
  EquipmentMajorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["EquipmentMajor"] = EquipmentMajorCB;
  
  EquipmentMinorCB = new QCheckBox(this);
  EquipmentMinorCB->setGeometry(xs[2], ys[0], checkBoxW, checkBoxH);
  EquipmentMinorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["EquipmentMinor"] = EquipmentMinorCB;
  
  EquipmentMissing2CB = new QCheckBox(this);
  EquipmentMissing2CB->setGeometry(xs[3], ys[0], checkBoxW, checkBoxH);
  EquipmentMissing2CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["EquipmentMissing2"] = EquipmentMissing2CB;
  
  EquipmentMissing3CB = new QCheckBox(this);
  EquipmentMissing3CB->setGeometry(xs[4], ys[0], checkBoxW, checkBoxH);
  EquipmentMissing3CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["EquipmentMissing3"] = EquipmentMissing3CB;
  
  //!
  SettingAllCB = new QCheckBox(this);
  SettingAllCB->setGeometry(xs[0], ys[1], checkBoxW, checkBoxH);
  SettingAllCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SettingAll"] = SettingAllCB;
  
  SettingMajorCB = new QCheckBox(this);
  SettingMajorCB->setGeometry(xs[1], ys[1], checkBoxW, checkBoxH);
  SettingMajorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SettingMajor"] = SettingMajorCB;
  
  SettingMinorCB = new QCheckBox(this);
  SettingMinorCB->setGeometry(xs[2], ys[1], checkBoxW, checkBoxH);
  SettingMinorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SettingMinor"] = SettingMinorCB;
  
  SettingMissing2CB = new QCheckBox(this);
  SettingMissing2CB->setGeometry(xs[3], ys[1], checkBoxW, checkBoxH);
  SettingMissing2CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SettingMissing2"] = SettingMissing2CB;
  
  SettingMissing3CB = new QCheckBox(this);
  SettingMissing3CB->setGeometry(xs[4], ys[1], checkBoxW, checkBoxH);
  SettingMissing3CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["SettingMissing3"] = SettingMissing3CB;
  
  //!
  ControlAllCB = new QCheckBox(this);
  ControlAllCB->setGeometry(xs[0], ys[3], checkBoxW, checkBoxH);
  ControlAllCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["ControlAll"] = ControlAllCB;
  
  ControlMajorCB = new QCheckBox(this);
  ControlMajorCB->setGeometry(xs[1], ys[3], checkBoxW, checkBoxH);
  ControlMajorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["ControlMajor"] = ControlMajorCB;
  
  ControlMinorCB = new QCheckBox(this);
  ControlMinorCB->setGeometry(xs[2], ys[3], checkBoxW, checkBoxH);
  ControlMinorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["ControlMinor"] = ControlMinorCB;
  
  ControlMissing2CB = new QCheckBox(this);
  ControlMissing2CB->setGeometry(xs[3], ys[3], checkBoxW, checkBoxH);
  ControlMissing2CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["ControlMissing2"] = ControlMissing2CB;
  
  ControlMissing3CB = new QCheckBox(this);
  ControlMissing3CB->setGeometry(xs[4], ys[3], checkBoxW, checkBoxH);
  ControlMissing3CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["ControlMissing3"] = ControlMissing3CB;
  
  //!
  AlarmAllCB = new QCheckBox(this);
  AlarmAllCB->setGeometry(xs[0], ys[4], checkBoxW, checkBoxH);
  AlarmAllCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["AlarmAll"] = AlarmAllCB;
  
  AlarmMajorCB = new QCheckBox(this);
  AlarmMajorCB->setGeometry(xs[1], ys[4], checkBoxW, checkBoxH);
  AlarmMajorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["AlarmMajor"] = AlarmMajorCB;
  
  AlarmMinorCB = new QCheckBox(this);
  AlarmMinorCB->setGeometry(xs[2], ys[4], checkBoxW, checkBoxH);
  AlarmMinorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["AlarmMinor"] = AlarmMinorCB;
  
  AlarmMissing2CB = new QCheckBox(this);
  AlarmMissing2CB->setGeometry(xs[3], ys[4], checkBoxW, checkBoxH);
  AlarmMissing2CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["AlarmMissing2"] = AlarmMissing2CB;
  
  AlarmMissing3CB = new QCheckBox(this);
  AlarmMissing3CB->setGeometry(xs[4], ys[4], checkBoxW, checkBoxH);
  AlarmMissing3CB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["AlarmMissing3"] = AlarmMissing3CB;
  
  //!
  MinimalMajorCB = new QCheckBox(this);
  MinimalMajorCB->setGeometry(xs[1], ys[5], checkBoxW, checkBoxH);
  MinimalMajorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["MinimalMajor"] = MinimalMajorCB;
  
  MinimalMinorCB = new QCheckBox(this);
  MinimalMinorCB->setGeometry(xs[2], ys[5], checkBoxW, checkBoxH);
  MinimalMinorCB->setStyleSheet("QCheckBox::indicator { width:11px; height:11px}");
  CheckBoxes["MinimalMinor"] = MinimalMinorCB;  
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
XMLCreateDialog::SlotOKButtonPressed()
{
  QList<QString>                        keys;

  keys = CheckBoxes.keys();

  for ( auto key : keys ) {
    Options->SetOption(key,CheckBoxes[key]->isChecked());
  }
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
XMLCreateDialog::SlotCancelButtonPressed()
{
  reject();
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
XMLCreateDialog::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   TopPaneW;
  int                                   TopPaneH;
  int                                   TopPaneY;
  int                                   TopPaneX;
  int                                   LeftPaneW;

  int                                   LeftPaneH;
  int                                   LeftPaneY;
  int                                   LeftPaneX;
  int                                   height;
  int                                   width;
  
  int                                   okX;
  int                                   okY;
  int                                   okW;
  int                                   okH;

  int                                   cancelX;
  int                                   cancelY;
  int                                   cancelW;
  int                                   cancelH;
  
  QSize                                 size;

  //!
  size = InEvent->size();
  height = size.height();
  width = size.width();
  
  LeftPaneX = 0;  
  LeftPaneY = TopPaneHeight;
  LeftPaneW = 120;
  LeftPaneH = height - TopPaneHeight;
  LeftPane->move(LeftPaneX, LeftPaneY);
  LeftPane->resize(LeftPaneW, LeftPaneH);

  cancelH = CancelButton->size().height();
  cancelW = CancelButton->size().width();
  cancelY = height - (cancelH + 5);
  cancelX = width - (cancelW + 5);
  
  okH = OKButton->size().height();
  okW = OKButton->size().width();
  okY = height - (okH + 5);
  okX = cancelX - (okW + 5);

  CancelButton->resize(cancelW, cancelH);
  CancelButton->move(cancelX, cancelY);

  OKButton->resize(okW, okH);
  OKButton->move(okX, okY);

  TopPaneX = 0;
  TopPaneY = 0;
  TopPaneW = width;
  TopPaneH = TopPaneHeight;
  TopPane->move(TopPaneX, TopPaneY);
  TopPane->resize(TopPaneW, TopPaneH);
}
