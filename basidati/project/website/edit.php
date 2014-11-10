<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
	<body>
		<?php require 'header.php'; ?>
		<div id="content">
			<?php				
				/* Controllo se devo modificare thread, post, sezione o user */
				if (isset($_GET['thread']))
				{
					$id = $_GET['thread'];
					$conn = db_auth();
					$thread = mysql_query("SELECT * FROM Threads WHERE Id=$id", $conn);
					if ($row = mysql_fetch_assoc($thread))
					{
						$content = $row['Content'];
						$title = $row['Title'];
						echo "<form action='processform.php?modthread=true&id=$id' method='post'>
									<p class='areatitle'>Edit Title: </p><br>
									<input type='text' name='title' value='$title' style='width:57%'><br>
									<p class='areatitle'>Edit Text: </p><br>
									<textarea name='text' rows='24' cols='120'>$content</textarea><br>
									<input type='submit' value='Update' style='margin:12px 0px 0px 0px' /><br>
									</form>";	
						if (isset($_GET['empty']))
						{
							echo "<p style='color:red'>EMPTY FIELDS DETECTED!</p>";
						}			
					}
				}
				else if (isset($_GET['post']))
				{
					$id = $_GET['post'];
					$conn = db_auth();
					$post = mysql_query("SELECT * FROM Posts WHERE Id='$id'", $conn);
					if ($row = mysql_fetch_assoc($post))
					{
						$content = $row['Content'];
						echo "<form action='processform.php?modpost=true&id=$id' method='post'>
									<p class='areatitle'>Edit Text: </p><br>
									<textarea name='text' rows='24' cols='120'>$content</textarea><br>
									<input type='submit' value='Update' style='margin:12px 0px 0px 0px' /><br>
									</form>";
						if (isset($_GET['empty']))
						{
							echo "<p style='color:red'>CONTENT CAN'T BE EMPTY!</p>";
						}	
					}								
				}
				else if (isset($_GET['section']))
				{
					$name = $_GET['section'];
					$conn = db_auth();
					$section = mysql_query("SELECT * FROM Sections WHERE Name='$name'", $conn);
					if ($row = mysql_fetch_assoc($section))
					{
						$description = $row['Description'];
						echo "<form action='processform.php?modsec=true&name=$name' method='post'>
									<p class='areatitle'>Edit Name: </p><br>
									<input type='text' name='title' value='$name' style='width:57%'><br>
									<p class='areatitle'>Edit Description: </p><br>
									<textarea name='description' rows='24' cols='120'>$description</textarea><br>
									<input type='submit' value='Update' style='margin:12px 0px 0px 0px' /><br>
									</form>";	
						if (isset($_GET['empty']))
						{
							echo "<p style='color:red'>EMPTY FIELDS DETECTED!</p>";
						}			
					}
				}
				else if (isset($_GET['user']))
				{
					$username = $_GET['user'];

					echo "<form action='processform.php?modusr=true&username=$username' method='post'>
								<p class='areatitle'>Edit username: </p><br>
								<input type='text' name='username' value='$username' style='width:57%'><br>
								<input type='submit' value='Update' style='margin:12px 0px 0px 0px' /><br>
								</form>";	
					if (isset($_GET['empty']))
					{
						echo "<p style='color:red'>EMPTY FIELDS DETECTED!</p>";
					}
					if (isset($_GET['exist']))
					{
						echo "<p style='color:red'>USERNAME ALREADY EXISTS!</p>";
					}				
				}				
			?>				
		</div>
	</body>
</html>
