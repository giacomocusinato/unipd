/* Clean the database first */

SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS Users;
DROP TABLE IF EXISTS Moderators;
DROP TABLE IF EXISTS Admins;
DROP TABLE IF EXISTS Threads;
DROP TABLE IF EXISTS ThreadDetails;
DROP TABLE IF EXISTS Sections;
DROP TABLE IF EXISTS Posts;
DROP TABLE IF EXISTS Conversations;
DROP TABLE IF EXISTS UserConversation;
DROP TABLE IF EXISTS Messages;

/* Create the tables */

SET FOREIGN_KEY_CHECKS=1;

CREATE TABLE Users (
	Username VARCHAR(20) PRIMARY KEY,
	Pwd VARCHAR(40) NOT NULL,
	Email VARCHAR(40) NOT NULL,
	RegDate DATE NOT NULL, 
	PostCount INT NOT NULL DEFAULT 0
) ENGINE = InnoDB;

CREATE TABLE Moderators (
	Username VARCHAR(20) NOT NULL,
	FOREIGN KEY (Username) REFERENCES Users(Username)
		ON DELETE CASCADE
		ON UPDATE CASCADE
)	ENGINE = InnoDB ; 

CREATE TABLE Admins (
	Username VARCHAR(20),
	FOREIGN KEY (Username) REFERENCES Users(Username)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE = InnoDB;

CREATE TABLE Sections (
	Name VARCHAR(50) PRIMARY KEY,
	Description VARCHAR(150),
	SupSection VARCHAR(50) DEFAULT "root"
) ENGINE = InnoDB;

ALTER TABLE Sections ADD CONSTRAINT Sections_ibfk_1
FOREIGN KEY (SupSection) REFERENCES Sections(Name)
	ON DELETE CASCADE
	ON UPDATE CASCADE;

CREATE TABLE Threads (
	Id INT PRIMARY KEY,
	Title VARCHAR(100) NOT NULL,
	Content VARCHAR(65000),
	PostDate DATE NOT NULL,
	Username VARCHAR(20) NOT NULL,
	SectionName VARCHAR(50) NOT NULL,
	FOREIGN KEY (Username) REFERENCES Users(Username)
		ON DELETE CASCADE
		ON UPDATE CASCADE,
	FOREIGN KEY (SectionName) REFERENCES Sections(Name)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE = InnoDB;

CREATE TABLE ThreadDetails (
	Id INT PRIMARY KEY,
	PostCount INT NOT NULL DEFAULT 0,
	LastModified DATE,
	LastMod VARCHAR(20),
		FOREIGN KEY (Id) REFERENCES Threads(Id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE = InnoDB;

CREATE TABLE Posts (
	Id INT PRIMARY KEY,
	Content VARCHAR(65000) NOT NULL,
	PostDate DATE NOT NULL,
	Username VARCHAR(20) NOT NULL,
	ThreadId INT NOT NULL,
	FOREIGN KEY (Username) REFERENCES Users(Username)
		ON DELETE CASCADE
		ON UPDATE CASCADE,	
	FOREIGN KEY (ThreadId) REFERENCES Threads(Id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE = InnoDB;


CREATE TABLE Conversations (
	Id INT PRIMARY KEY,
	Obj VARCHAR(100) NOT NULL
) ENGINE = InnoDB;

CREATE TABLE UserConversation (
	Username VARCHAR(20) NOT NULL,
	Id INT NOT NULL,
	FOREIGN KEY (Username) REFERENCES Users(Username)
		ON DELETE CASCADE
		ON UPDATE CASCADE,
	FOREIGN KEY (Id) REFERENCES Conversations(Id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE = InnoDB;


CREATE TABLE Messages (
	Id INT PRIMARY KEY,
	Content VARCHAR(65000) NOT NULL,
	PostDate DATE NOT NULL,
	Username VARCHAR(20) NOT NULL,
	Conversation INT NOT NULL,
		FOREIGN KEY (Username) REFERENCES Users(Username)
		ON DELETE CASCADE
		ON UPDATE CASCADE,
	FOREIGN KEY (Conversation) REFERENCES Conversations(Id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE = InnoDB;

/* Load the data */

/*LOAD DATA LOCAL INFILE '/home/1/2012/gcusinat/Basi/project/data/users.txt' INTO TABLE Users;*/
INSERT INTO Users (Username, Pwd, Email, RegDate, PostCount)
VALUES
('gcusinat', 'root123', 'gcus@live.it', '2014-04-11', 0),
('micalleg', 'psw13', 'mcall@outlook.com', '2014-05-05', 0);

INSERT INTO Admins (Username)
VALUES ('gcusinat');
INSERT INTO Moderators (Username)
VALUES ('micalleg');

SET FOREIGN_KEY_CHECKS = 0;
INSERT INTO Sections (Name, Description, SupSection)
VALUES
('Cases and Power Supplies', '', 'root'),
('CPUs, Motherboards, and Memory', 'General Discussion, Overclocking, and Troubleshooting', 'root'),
('Graphics Card', 'General Discussion, Overclocking, and Troubleshooting', 'root'),
('Power Supplies', 'All about PSUs', 'Cases and Power Supplies'),
('Cases', 'All about PC cases', 'Cases and Power Supplies'),
('Tech News and Reviews', 'News & Review from all around the web', 'root');	
SET FOREIGN_KEY_CHECKS = 1;

/* Add the triggers */

DELIMITER $$

DROP TRIGGER IF EXISTS UpdatePostCount$$
CREATE TRIGGER UpdatePostCount
AFTER INSERT ON Posts
FOR EACH ROW
BEGIN
	DECLARE usr VARCHAR(20);
	DECLARE thread VARCHAR(20);
	SET usr = (SELECT u.Username
			   FROM Users u
	           WHERE u.Username = new.Username);
	SET thread = (SELECT p.ThreadId
				  FROM Posts p
				  WHERE p.Id = new.Id);			   
	IF usr IS NOT NULL THEN
		UPDATE Users
		SET PostCount = PostCount + 1
		WHERE Username = usr;
	END IF;
	IF thread IS NOT NULL THEN
		UPDATE ThreadDetails
		SET PostCount = PostCount + 1
		WHERE Id = thread;
	END IF;	
END$$

DROP TRIGGER IF EXISTS DecreasePostCount$$
CREATE TRIGGER DecreasePostCount
AFTER DELETE ON Posts
FOR EACH ROW
BEGIN
	DECLARE usr VARCHAR(20);
	DECLARE thread VARCHAR(20);
	SET usr = (SELECT u.Username
			   FROM Users u
	           WHERE u.Username = old.Username);
	SET thread = (SELECT p.ThreadId
				  FROM Posts p
				  WHERE p.Id = old.Id);			   
	IF usr IS NOT NULL THEN
		UPDATE Users
		SET PostCount = PostCount - 1
		WHERE Username = usr;
	END IF;
	IF thread IS NOT NULL THEN
		UPDATE ThreadDetails
		SET PostCount = PostCount - 1
		WHERE Id = thread;
	END IF;	
END$$

/* Add the functions */

DROP FUNCTION IF EXISTS MostActiveUser$$
CREATE FUNCTION MostActiveUser () RETURNS VARCHAR(20)
BEGIN
	DECLARE name VARCHAR(20);
	DECLARE pCount INT;
	SELECT max(PostCount) INTO pCount FROM Users;
	SELECT Username INTO name FROM Users WHERE PostCount=pCount LIMIT 1;
	RETURN name;
END$$

DROP FUNCTION IF EXISTS HasPosted$$
CREATE FUNCTION HasPosted (usr VARCHAR(20)) RETURNS BOOLEAN
BEGIN
	DECLARE name VARCHAR(20);
	DECLARE posted BOOLEAN;
	SELECT Username INTO name
	FROM Posts 
	WHERE Username = usr
	GROUP BY Username;
	IF name IS NOT NULL
		THEN
			SET posted = 1;
		ELSE
			SET posted = 0;
	END IF;
	RETURN posted;
END$$

DELIMITER ;