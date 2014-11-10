<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
<body>
	<?php include "header.php" ?>
	<div id='content'>
		<?php			
			/* Creo il tread */
			$id = $_GET['id'];
			$conn = db_auth();
			$thread = mysql_query("SELECT * FROM Threads WHERE Id='$id'", $conn);
			if ($row = mysql_fetch_assoc($thread))
			{
				$title = strtoupper($row['Title']);
				$content = $row['Content'];
				$postdate = $row['PostDate'];
				$username = $row['Username'];;
				
				echo "<table border='2' cellspacing='0' cellpadding='12'>
							<tr>
								<td>
									<h2 class='thread'>$title</h2>
									<p style='color:white'>$content</p>
									<p class='thread'>posted by $username on $postdate</p>";
								
				if(is_logged() && is_mod())				
					echo "<form action='processform.php?managethread=true&id=$id' method='post'>
									<input type='submit' value='Delete' name='action'/>
									<input type='submit' value='Update' name='action'/>
								</form>";
								
			  echo "</td>
						  </tr>
					  	</table>";
			}
			
			/* Label il numero di post presenti */
			$posts = mysql_query("SELECT Count(Id) as Total FROM Posts WHERE ThreadId='$id'", $conn);
			if ($row = mysql_fetch_assoc($posts))
			{
				$count = $row['Total'];
				echo "<h3 class='responses'>$count RESPONSES TO THIS THREAD</h3>";
			}
			else
			{
				echo "<h3 class='responses'>0 RESPONSES TO THIS THREAD</h3>";
			}
			
			/* Lista posts */
			$posts = mysql_query("SELECT * FROM Posts WHERE ThreadId='$id'", $conn);
			echo "<table border='2' cellspacing='0' cellpadding='12'>";
			while ($row = mysql_fetch_assoc($posts))
			{
				$content = $row['Content'];
				$postdate = $row['PostDate'];
				$username = $row['Username'];
				$post_id = $row['Id'];
				
				echo "<tr>
						<td>
							<p style='color:white'>$content</p>
							<p class='thread'>posted by $username on $postdate</p>";
				if (is_logged() && is_mod())
				{		
					echo "<form action='processform.php?managepost=true&id=$post_id' method='post'>
									<input type='submit' value='Delete' name='action'/>
									<input type='submit' value='Update' name='action'/>
								</form>";
				}
				echo	"</td>
					  </tr>";
			}
			echo "</table>";
			
			/* Form per nuovo post */
			echo "<form action='processform.php?newpost=true&id=$id' method='post'>
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
				echo "<p style='color:red'>TITLE CAN'T BE EMPTY</p>";
			}
		?>
		
	<div>
	<!-- /close div content tag -->
</body>
</html>
