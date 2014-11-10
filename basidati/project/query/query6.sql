/* Per ogni utente ritorna il numero di conversazioni a cui partecipa e il numero di messaggi inviate */
SELECT uc.Username,  COUNT(uc.Id) AS Conversations, COUNT(m.Id) as Messages
FROM UserConversation uc JOIN Messages m ON (uc.Username = m.Username)
GROUP BY m.Username
UNION
SELECT uc.Username, COUNT(uc.Id), COUNT(null)
FROM UserConversation uc
WHERE uc.Username NOT IN (
											 SELECT m.Username
											 FROM Messages m
										  )
GROUP BY uc.Username 
UNION
SELECT u.Username, COUNT(null), COUNT(null)
FROM Users u
WHERE u.Username NOT IN (
											SELECT uc.Username 
											FROM UserConversation uc
										)
GROUP BY u.Username