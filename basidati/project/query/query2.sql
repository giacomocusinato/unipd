/* Ritorna gli utenti che hanno aperto un thread in almeno due sezioni diverse */

DROP VIEW IF EXISTS UserSections;
CREATE VIEW UserSections AS
SELECT t.Username, COUNT(t.SectionName) AS SectionsNumber
FROM Threads t
GROUP BY t.Username;

SELECT Username
FROM UserSections
WHERE SectionsNumber > 1;


