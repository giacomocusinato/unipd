<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
<body>
	<?php include "header.php" ?>
	<div id='content'>
		<?php 			
			/* Solo gli admin possono accedere a quest'area */
			if (!is_admin())
			{
				echo "<p style='font-family:helvetica'>Restricted area. Only admins have access to this page.</p>";
				exit;
			}
		?>
		<form action='processform.php?adminarea=true' method='post'>
		  <h3>Action:</h3>
			<input type="radio" name="action" value="update">Update
			<input type="radio" name="action" value="delete">Delete
		  <h3>Object:</h3>
			<input type="radio" name="object" value="section">Section
			<input type="radio" name="object" value="user">User
			<p></p>
			Section/User name: <input type="text" name="name">
			<p></p>
			<input type="submit" value="Confirm">
		</form>
		<?php
			if (isset($_GET['nosec']))
			{
				echo "<p style='color:red'>ENTERED SECTION DOES NOT EXIST. PLEASE, TRY AGAIN</p>";
			}
			if (isset($_GET['secdel']))
			{
				echo "<p style='color:red'>SECTION DELETED SUCCESSFULLY!</p>";
			}
			if (isset($_GET['nousr']))
			{
				echo "<p style='color:red'>ENTERED USER DOES NOT EXIST. PLEASE, TRY AGAIN</p>";
			}
			if (isset($_GET['usrdel']))
			{
				echo "<p style='color:red'>USER DELETED SUCCESSFULLY!</p>";
			}
			if (isset($_GET['usrup']))
			{
				echo "<p style='color:red'>USERNAME UPDATED SUCCESSFULLY!</p>";
			}
		?>
	<div>
</body>
</html>
