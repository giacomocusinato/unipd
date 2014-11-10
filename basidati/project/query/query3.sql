/* Ritorna i threads con il numero massimo di post per ogni sezione */

DROP VIEW IF EXISTS HelperView;
CREATE VIEW HelperView AS
SELECT t.Title, Count(p.Id) AS PostCount, t.SectionName
FROM Threads t JOIN Posts p ON (p.ThreadId = t.Id)
GROUP BY t.Id;

SELECT Title
FROM HelperView
GROUP BY SectionName
HAVING MAX(PostCount);
