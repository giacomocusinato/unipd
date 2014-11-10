<html>
	<head>
		<title>REGISTER</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
	<body>
	<?php require 'header.php'; ?>
	<div id="content">
		<form name='modulo' action='processform.php?reg=true' method='post'>
			<table border="0" cellspacing="5" cellpadding="5">
				<tr>
					<td class="formtext">Username:</td><td><input type="text" name="username"></td>
				</tr>
				<tr>
					<td class="formtext">Email:</td><td><input type="text" name="email"></td>
				</tr>
				<tr>
					<td class="formtext">Password:</td><td><input type="password" name="pwd1"></td>
				</tr>
				<tr>
					<td class="formtext">Confirm Password:</td><td><input type="password" name="pwd2"></td>
				</tr>
				<tr>
					<td></td><td><input type="submit" value="Confirm">
				  <input type=reset value="Reset"></td></tr></td>
				</tr>
			<table>
		</form>	
	<div>
	<!-- /close content div -->
		<?php
			if ($_GET)
			{
				$m = $_GET['m'];
				switch ($m)
				{
					case "empty": echo "Some filels are empty. Fill out the form and try again.";
						break;
					case "password": echo "The password fields did not match.";
						break;
					case "username": echo "The username is already in use.";
						break;
					case "email": echo "The email address is already in use.";
						break;
				}
			}
		?>
	</body>
</html>


