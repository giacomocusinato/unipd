<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
	<body>
		<?php require 'header.php'; ?>
		<div id="content">
			<?php 								
				if (!is_logged())
				{
					echo "<p class='formtext'><a href='register.php' style='color:white'>Register</a> or login in order to access your conversations.</p>";
					exit;
				}
				else
				{
					/* Header numero conversazioni */
					$conn = db_auth();
					$userinfo = $_SESSION['userinfo'];
					$username = $userinfo['Username'];
					$conversations = mysql_query("SELECT Count(Id) as Total FROM UserConversation WHERE Username = '$username'", $conn);
				  $row = mysql_fetch_assoc($conversations);
				  $count = $row['Total'];
				  if ($count != 1)
				  	echo "<h3 class='responses'>$count CONVERSATIONS</h3>";
				  else
				  	echo "<h3 class='responses'>1 CONVERSATION</h3>";
				}
			?>
			<table border='4' cellspacing='0' cellpadding='12'>
				<tr>
					<td>
						<?php
							echo "<a href='newconversation.php' class='section'>NEW CONVERSATION...</a>";
						?>
					</td>
				</tr>
				<?php
					/* Visualizzo le conversazioni */
					$conn = db_auth();
					$userinfo = $_SESSION['userinfo'];
					$username = $userinfo['Username'];
					$conversations = mysql_query("SELECT c.Id, c.Obj
												  FROM Conversations c NATURAL JOIN UserConversation u 
												  WHERE u.Username = '$username' GROUP BY c.Id", 
												  $conn);
					while ($row = mysql_fetch_assoc($conversations))
					{
						$obj = strtoupper($row['Obj']);
						$id = $row['Id'];
						echo "<tr>
								  <td><a href='conversation.php?id=$id' class='section'><h4>$obj<h4><a></td>
							  </tr>";
					}
				?>
		 	</table>
		</div>
		<!-- /close content container -->
	</body>
</html>
