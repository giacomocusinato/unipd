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
					<td class='tablehead'>Sections</td>
					<td class='tablehead'>Threads</td>
					<td class='tablehead'>Post</td>
				</tr>
					<?php			
						$conn = db_auth();
						$sections = mysql_query("SELECT * FROM Sections WHERE SupSection='root'", $conn);
						/* Scorro tutte le sezioni presenti nel db */
						while($sec = mysql_fetch_assoc($sections))
						{
							$name = $sec['Name'];
							$descr = $sec['Description'];
							echo "<tr>
											<td>
												<a href='section.php?title=$name' class='section'><h3>$name</h3></a>
												<font color='white'>$descr</font>";
							
							/* Controllo se sono presenti sottosezioni */
							$subSections = mysql_query("SELECT * FROM Sections WHERE SupSection!='root'", $conn);	
							while($subsec = mysql_fetch_assoc($subSections))
							{
								$sname = $subsec['Name'];
								$sdescr = $subsec['Description'];
								$sup = $subsec['SupSection'];
								if ($sup==$name)
								{
									 echo "<span class='rectangle'></span><a href='section.php?title=$sname' class='subsection'>$sname</a>";
								}
							}
							echo "</td>";
							
							/* Riempio le restanti righe, npost, nthread */
							$total = mysql_query("SELECT Count(*) as Total FROM Threads WHERE SectionName='$name'", $conn);
							$row = mysql_fetch_assoc($total);
							$nthread = $row['Total'];
							echo "<td class='number'>$nthread</td>";
							
							$total = mysql_query("SELECT Count(p.Id) as Total FROM Posts p, Threads t WHERE t.SectionName='$name' AND p.ThreadId = t.Id", $conn);
							$row = mysql_fetch_assoc($total);
							$npost= $row['Total'];
							echo "<td class='number'>$npost</td>";
						} 
				 	?>
			 	</tr>
		 	</table>
		</div>
		<!-- /close content container -->
	</body>
</html>
