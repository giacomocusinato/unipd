/* Ritorna  tutti i thread modificati da moderatori nella giornata corrente */

SELECT t.Title, m.Username
FROM ThreadDetails td NATURAL JOIN Threads t, Moderators m
WHERE td.LastMod = m.Username AND td.LastModified IN (
																					 SELECT CURDATE()
																				  )
GROUP BY t.Title