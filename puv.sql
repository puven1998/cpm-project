CREATE DATABASE IF NOT EXISTS lejen;
USE lejen;
CREATE TABLE IF NOT EXISTS puv
(
	Activity VARCHAR(100),
	Duration INT,
	Earliest_Start INT,
	Earliest_Finish INT,
	Latest_Start INT,
	Latest_Finish INT,
	Slack INT,
	Firstnode INT,
	Predecessors VARCHAR(100),
	Activities_that_have_current_activity_as_predecessor VARCHAR(100),
	Unit_of_time VARCHAR(30)
);
INSERT INTO puv VALUES('cc',4,22,26,22,26,0,0,'d,e',NULL,'mths');
INSERT INTO puv VALUES('d',3,0,3,19,22,19,1,NULL,'cc','mths');
INSERT INTO puv VALUES('e',22,0,22,0,22,0,1,NULL,'cc','mths');
