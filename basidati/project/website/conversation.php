<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
<body>
	<?php include "header.php" ?>
	<div id='content'>
		<?php			
			/* Stampo l'oggetto della conversazione */
			$id = $_GET['id'];
			$conn = db_auth();
			$conv = mysql_query("SELECT * FROM Conversations WHERE Id='$id'", $conn);
			if ($row = mysql_fetch_assoc($conv))
			{
				$obj = strtoupper($row['Obj']);
				echo "<h3 class='responses'>$obj</h3>";
			}
			
			/* Stampo i partecipanti */
			echo "<p class='thread'>Partecipants: ";
			$users = mysql_query("SELECT u.Username FROM UserConversation uc NATURAL JOIN Users u WHERE uc.Id=$id", $conn);
			if ($row = mysql_fetch_assoc($users))
			{
				$usr = $row['Username'];
				echo "$usr";
			}
			while ($row = mysql_fetch_assoc($users))
			{
				$usr = $row['Username'];
				echo ", $usr";				
			}
			echo "</p>";
			
			/* Lista messaggi */
			$mess = mysql_query("SELECT * FROM Messages WHERE Conversation='$id'", $conn);
			echo "<table border='2' cellspacing='0' cellpadding='12'>";
			while ($row = mysql_fetch_assoc($mess))
			{
				$content = $row['Content'];
				$postdate = $row['PostDate'];
				$username = $row['Username'];
				
				echo "<tr>
						<td>
							<p style='color:white'>$content</p>
							<p class='thread'>posted by $username on $postdate</p>
						</td>
					  </tr>";
			}
			echo "</table>";
			
			/* Form per nuovo messaggio */
			echo "<form action='processform.php?newmess=true&id=$id' method='post'>
					<p class='areatitle'>Text: </p><br>
				    <textarea name='text' rows='24' cols='120'></textarea><br>";
			if (is_logged())
			{
				echo "<input type='submit' value='Post' style='margin:12px 0px 0px 0px' /><br>
					  </form>";
			}
			else
			{
				echo "<p class='formtext'><a href='register.php' style='color:white'>Register</a> or login in order to post new content in the forum</p>
					  </form>";
			}
			if (isset($_GET['empty']))
			{
				echo "<p style='color:red'>MESSAGE CAN'T BE EMPTY</p>";
			}
		?>
		
	<div>
	<!-- /close div content tag -->
</body>
</html>
