/* Ritorna i nomi degli utenti che hanno avuto almeno una conversazione con un admin */

SELECT uc.Username
FROM UserConversation uc
WHERE uc.Id NOT IN (
											SELECT c.Id
											FROM UserConversation uc2 NATURAL JOIN Conversations c
											WHERE uc2.Username NOT IN (
																							SELECT * 
																							FROM Admins
																						) 
																						 AND c.Id NOT IN (
																													 SELECT uc3.Id 
																													 FROM UserConversation uc3 
																													 WHERE uc3.Username IN   (
																					 											 	 	                     	 SELECT * 
																					 											 	 	                     	 FROM Admins
																																							)
																												  )
							   )
										AND uc.Username NOT IN (SELECT * FROM Admins)
