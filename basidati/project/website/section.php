<html>
	<head>
		<title>THE TEK</title>
		<link href="style.css" rel="stylesheet" type="text/css">
	</head>
	<body>
		<?php require 'header.php'; ?>
		<div id="content">
			<table border='4' cellspacing='0' cellpadding='12'>
				<tr>
					<?php 
						$conn = db_auth();
						$title = $_GET['title'];
						$section = mysql_query("SELECT * FROM Sections WHERE Name='$title'", $conn);
						if ($sec = mysql_fetch_assoc($section))
						{
							$descr = $sec['Description'];
							echo "<td>
												<h2 class='section'>$title</h2>
												<font color='white'>$descr</font>";
							/* Controllo se sono presenti sottosezioni */
							$subSections = mysql_query("SELECT * FROM Sections WHERE SupSection='$title'", $conn);	
							while($subsec = mysql_fetch_assoc($subSections))
							{
								$sname = $subsec['Name'];
								$sdescr = $subsec['Description'];
								echo "<span class='rectangle'></span><a href='section.php?title=$sname' class='subsection'>$sname</a>";
							}
						}
					?>
					</td>
				<tr>
					<td>
						<?php
							$section = $_GET['title']; 
							echo "<a href='newthread.php?sec=$title' class='section'>NEW THREAD...</a>";
						?>
					</td>
				</tr>
				<?php
					/* Visualizzo i thread */
					$conn = db_auth();
					$section = $_GET['title'];
					$thread = mysql_query("SELECT t.Id, t.Title FROM Threads t WHERE t.SectionName='$section' ORDER BY t.Id DESC", $conn);
					while ($row = mysql_fetch_assoc($thread))
					{
						$title = strtoupper($row['Title']);
						$id = $row['Id'];
						echo "<tr>
								  <td><a href='thread.php?id=$id' class='section'><h4>$title<h4><a></td>
								  </tr>";
					}
				?>
		 	</table>
		</div>
		<!-- /close content container -->
	</body>
</html>
