PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE ElementDisplay (SignalTypeName text, LineOrder integer, ElementKey text, ElementName text, DifferenceSeverity text, LineHeightMultiplier integer);
INSERT INTO ElementDisplay VALUES('Alarm',1,'AlarmName','Alarm Name','Major',1);
INSERT INTO ElementDisplay VALUES('Alarm',2,'Level','Level','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',3,'ExpRPN','Expression RPN','Major',2);
INSERT INTO ElementDisplay VALUES('Alarm',4,'ExpFull','Expression Full','Major',1);
INSERT INTO ElementDisplay VALUES('Alarm',5,'Delay','Delay','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',6,'SuppressRPN','Suppress RPN','Major',2);
INSERT INTO ElementDisplay VALUES('Alarm',7,'SuppressFull','Suppress Full','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',8,'Relay','Relay','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',9,'Help','Help','Minor',1);
INSERT INTO ElementDisplay VALUES('Equipment',0,'Type','Type','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',1,'Name','Name','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',2,'TypeName','Type Name','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',3,'GroupName','Group Name','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',4,'NumofSamples','Number of Samples','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',5,'NumofCtrl','Number of Controls','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',6,'NumofSet','Number of Settings','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',7,'NumofAlarm','Number of Alarms','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',8,'Related','Related','Major',5);
INSERT INTO ElementDisplay VALUES('Settings',0,'SETName','Setting Name','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',1,'Unit','Unit','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',2,'SIndx','Signal Indx','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',3,'SChan','Signal Channel','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',4,'ValType','Value Type','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',5,'Def','Defaults','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',6,'Range','Range','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',7,'DisplayAttr','Display Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',8,'SetAttr','Set Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',9,'SetExpRPN','Settting Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',10,'SetExpFull','Setting Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Settings',11,'Auth','Auth','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',12,'DisplayID','Display ID','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',13,'DispFmt','Display Format','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',14,'ChID','Channel ID','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',15,'Step','Step','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',16,'CExpRPN','Channel Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',17,'CExpFull','Channel Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Settings',18,'Persist','Persist','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',19,'DispExpRPN','Display Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',20,'DispExpFull','Display Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Settings',21,'States','States','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',22,'OnCtrl','On Control','Major',1);
INSERT INTO ElementDisplay VALUES('Control',0,'CTRLName','CTRLName','Major',1);
INSERT INTO ElementDisplay VALUES('Control',1,'Unit','Unit','Major',1);
INSERT INTO ElementDisplay VALUES('Control',2,'SIndx','Signal Indx','Major',1);
INSERT INTO ElementDisplay VALUES('Control',3,'SChan','Signal Chan','Major',1);
INSERT INTO ElementDisplay VALUES('Control',4,'ValType','Value Type','Major',1);
INSERT INTO ElementDisplay VALUES('Control',5,'Defaults','Defaults','Major',1);
INSERT INTO ElementDisplay VALUES('Control',6,'Range','Range','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',7,'DisplayAttr','Display Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',8,'CtrlAttr','Control Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',9,'Threshold','Threshold','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',10,'CableExpRPN','Cable Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Control',11,'CableExpFull','Cable Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Control',21,'Auth','Auth','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',13,'DisplayID','Display ID','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',14,'DispFmt','Display Format','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',15,'ChID','Channel ID','Major',1);
INSERT INTO ElementDisplay VALUES('Control',16,'CStep','Channel Step','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',17,'CParam','Channel Parameter','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',18,'CexpRPN','Channel Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Control',19,'CexpFullDispExp','Channel Expression Full Display Expression','Major',0);
INSERT INTO ElementDisplay VALUES('Control',20,'States','States','Major',1);
INSERT INTO ElementDisplay VALUES('Control',21,'CAction','Channel Action','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',0,'SAMPLEName','Sample Name','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',1,'Unit','Unit','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',2,'SIndx','Signal Index','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',3,'SChan','Signal Channel','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',4,'ValType','Value Type','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',5,'StorThreshold','Store Threshold','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',6,'StorInt','Store Int','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',7,'EvalExpRPN','Eval Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',8,'EvalExpFull','Eval Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Samples',9,'Range','Range','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',10,'DisplayAttr','Display Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',11,'DisplayLvl','Display Level','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',12,'DisplayID','Display ID','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',13,'DispFmt','Display Format','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',14,'DispExpRPN','Display Expression RPN','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',15,'DispExpFull','Display Expression Full','Minor',0);
INSERT INTO ElementDisplay VALUES('Samples',16,'Enums','Enums','Major',1);
COMMIT;
