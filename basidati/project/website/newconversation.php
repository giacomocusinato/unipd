<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
	<body>
		<?php require 'header.php'; ?>
		<div id="content">
			<?php
				echo "<form action='processform.php?newconv=true' method='post'>"
			?>
				<p class="areatitle">Receivers (separated by commas): </p><br>
				<input type="text" name="receivers" style="width:57%"><br>
				<p class="areatitle">Object: </p><br>
				<input type="text" name="object" style="width:57%"><br>				
				<p class="areatitle">Text: </p><br>
				<textarea name="text" rows="24" cols="120"></textarea><br>
				<?php
					/* Controllo se l'utente e' loggato */
					if (is_logged())
					{
						echo "<input type='submit' value='Send' style='margin:12px 0px 0px 0px' /><br>
							  </form>";
					}
					else
					{
						echo "<p class='formtext'><a href='register.php' style='color:white'>Register</a> or login in order to access your conversations.</p>
							  </form>";
					}
					
					if (isset($_GET['empty']))
					{
						echo "<p style='color:red'>SOME FILES ARE EMPTY. PLEASE; FILL THE FORM AND TRY AGAIN</p>";
					}
					if (isset($_GET['receivers']))
					{
						echo "<p style='color:red'>RECEIVERS FIELD IS NOT VALID</p>";
					}
				?>				

		</div>
		<!-- /close content container -->
	</body>
</html>
