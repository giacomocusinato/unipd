/* Ritorna titolo, data e nuomero di post di tutti i thread aperti da moderatori con almeno due conversazioni attive */

SELECT t.Title, t.PostDate, COUNT(p.Id) AS PostCount
FROM Threads t JOIN Posts p ON (p.ThreadId = t.Id)
WHERE t.Username IN (
									SELECT u.Username 
									FROM Users u NATURAL JOIN Moderators m
									WHERE 2 <= (
															SELECT COUNT(*) 
															FROM UserConversation uc 
															WHERE uc.Username=u.Username
														)						 	
								 )
GROUP BY t.Id;
