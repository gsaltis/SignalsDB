PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE ElementDisplay (SignalTypeName text, LineOrder integer, ElementKey text, ElementName text, DifferenceSeverity text, LineHeightMultiplier integer);

INSERT INTO ElementDisplay VALUES('Alarm',0,'AlarmName','Alarm Name','Major',1);
INSERT INTO ElementDisplay VALUES('Alarm',1,'ResourceID','Resource ID','Major',1);
INSERT INTO ElementDisplay VALUES('Alarm',2,'Level','Level','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',3,'AlarmExprRPN','Alarm Expression RPN','Major',2);
INSERT INTO ElementDisplay VALUES('Alarm',4,'AlarmExprFull','Alarm Expression Full','Major',1);
INSERT INTO ElementDisplay VALUES('Alarm',5,'Delay','Delay','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',6,'SuppressExprRPN','Suppress Expression RPN','Major',2);
INSERT INTO ElementDisplay VALUES('Alarm',7,'SuppressExprFull','Suppress Expression Full','Major',1);
INSERT INTO ElementDisplay VALUES('Alarm',8,'RelayNumber','Relay Number','Minor',1);
INSERT INTO ElementDisplay VALUES('Alarm',9,'HelpInfo','Help Info','Minor',1);


INSERT INTO ElementDisplay VALUES('Equipment',0,'Type','Type','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',1,'Name','Name','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',2,'TypeName','Type Name','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',3,'GroupName','Group Name','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',4,'NumberOfSamples','Number Of Samples','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',5,'NumberOfCtrl','Number Of Ctrl','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',6,'NumberOfSet','Number Of Set','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',7,'NumberOfAlarm','Number Of Alarm','Major',1);
INSERT INTO ElementDisplay VALUES('Equipment',8,'Related','Related','Major',5);


INSERT INTO ElementDisplay VALUES('Settings',0,'SettingName','Setting Name','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',1,'ResourceID','Resource ID','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',2,'Unit','Unit','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',3,'SamplerIndex','Sampler Index','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',4,'SamplerChannel','Sampler Channel','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',5,'ValueType','Value Type','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',6,'Defaults','Defaults','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',7,'Range','Range','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',8,'DisplayAttr','Display Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',9,'SetAttr','Set Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',10,'SetExprRPN','Set Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',11,'SetExprFull','Set Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Settings',12,'AuthLevel','Authority Level','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',13,'DisplayID','Display ID','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',14,'DisplayFormat','Display Format','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',15,'ChannelID','Channel ID','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',16,'ControlStep','ControlStep','Minor',1);
INSERT INTO ElementDisplay VALUES('Settings',17,'ControlExprRPN','Control Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',18,'ControlExprFull','Control Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Settings',19,'PersistentFlag','Persistent Flag','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',20,'OnControlAction','On Control Action','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',21,'DisplayExprRPN','Display Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Settings',22,'DisplayExprFull','Display Expression Full','Major',0);
INSERT INTO ElementDisplay VALUES('Settings',23,'States','States','Major',1);


INSERT INTO ElementDisplay VALUES('Control',0,'ControlName','Control Name','Major',1);
INSERT INTO ElementDisplay VALUES('Control',1,'ResourceID','Resource ID','Major',1);
INSERT INTO ElementDisplay VALUES('Control',2,'Unit','Unit','Major',1);
INSERT INTO ElementDisplay VALUES('Control',3,'SamplerIndx','Sampler Indx','Major',1);
INSERT INTO ElementDisplay VALUES('Control',4,'SamplerChannel','Sampler Channel','Major',1);
INSERT INTO ElementDisplay VALUES('Control',5,'ValueType','Value Type','Major',1);
INSERT INTO ElementDisplay VALUES('Control',6,'Defaults','Defaults','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',7,'Range','Range','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',8,'DisplayAttr','Display Attr','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',9,'ControlAttr','Control Attr','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',10,'Threshold','Threshold','Major',1);
INSERT INTO ElementDisplay VALUES('Control',11,'CableExprRPN','Cable Expr RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Control',12,'CableExprFull','Cable Expr Full','Major',1);
INSERT INTO ElementDisplay VALUES('Control',13,'AuthLevel','Authority Level','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',14,'DisplayID','Display ID','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',15,'DisplayFormat','Display Format','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',16,'ChannelID','Channel ID','Major',1);
INSERT INTO ElementDisplay VALUES('Control',17,'ControlStep','Control Step','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',18,'ControlParam','Control Param','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',19,'ControlExprRPN','Control Expr RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Control',20,'ControlExprFull','Control Expr Full','Major',1);
INSERT INTO ElementDisplay VALUES('Control',21,'States','States','Major',1);
INSERT INTO ElementDisplay VALUES('Control',22,'OnControlAction','On Control Action','Minor',1);
INSERT INTO ElementDisplay VALUES('Control',23,'DispExprRPN','Display Expr RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Control',24,'DispExprFull','Display Expr Full','Major',1);

INSERT INTO ElementDisplay VALUES('Samples',0,'SampleName','Sample Name','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',1,'ResourceID','Resource ID','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',2,'Unit','Unit','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',3,'SamplerIndex','Sampler Index','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',4,'SamplerChannel','Sampler Channel','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',5,'ValueType','ValueType','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',6,'StoringThreshold','Storing Threshold','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',7,'StoringInterval','Storing Interval','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',8,'EvalExprRPN','Eval Expression RPN','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',9,'EvalExprFull','Eval Expression Full','Major',1);
INSERT INTO ElementDisplay VALUES('Samples',10,'Range','Range','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',11,'DisplayAttr','Display Attribute','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',12,'DisplayLevel','Display Level','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',13,'DisplayID','Display ID','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',14,'DisplayFormat','Display Format','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',15,'DisplayExprRPN','Display Expression RPN','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',16,'DisplayExprFull','Display Expression Full','Minor',1);
INSERT INTO ElementDisplay VALUES('Samples',17,'Enums','Enums','Minor',1);

COMMIT;
