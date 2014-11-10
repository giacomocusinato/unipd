<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
	<body>
		<?php require 'header.php'; ?>
		<div id="content">
			<?php
				$section = $_GET['sec'];
				/* Devo aggiungere un thread a l db */
				echo "<form action='processform.php?newthread=true&sec=$section' method='post'>
								<p class='areatitle'>Title: </p><br>
								<input type='text' name='title' style='width:57%'><br>
								<p class='areatitle'>Text: </p><br>
								<textarea name='text' rows='24' cols='120'></textarea><br>";

				/* Controllo se l'utente e' loggato */
				if (is_logged())
				{
					echo "<input type='submit' value='Publish' style='margin:12px 0px 0px 0px' /><br>
							</form>";
				}
				else
				{
					echo "<p class='formtext'><a href='register.php' style='color:white'>Register</a> or login in order to post new content in the forum</p>
							</form>";
				}
		
				if (isset($_GET['empty']))
				{
					echo "<p style='color:red'>TITLE CAN'T BE EMPTY</p>";
				}
			?>				

		</div>
	</body>
</html>
