<div id="header">
	<table id="headtable">
		<tr>
			<td>
		 		<a href="home.php" id="title"><strong>THE TEK || FORUM</strong></a>
		  </td>
		  <td align="right">
		  <?php
	  		require "functions.php";
		  	session_start();
		  	$userinfo = $_SESSION['userinfo'];
		  	if ($userinfo)
		  	{
		  		$username = $userinfo['Username'];
				  $postcount = post_count($username);
		  		echo "<br><table border='0' cellspacing='3' cellpadding='0'>
		  											<tr></tr>
									<tr>
										<td class='option'>Welcome back, $username ($postcount posts)</td>
									</tr>
									<tr>
										<td>
											<form action='processform.php?logout=true' method='post' align=right>
												<input type='submit' value='Log Out'>
											</form>
										</td>
									</tr>
									<tr>
									<td><br></td>
									<tr>
								</table>";
				}
				else
				{
		  ?>
		  	<form action='processform.php?login=true' method='post'>
					<table border="0" cellspacing="3" cellpadding="0">
						<tr>
							<td class="formtext">User Name:</td>
							<td><input type="text" name="username"></td>
						</tr>
						<tr>
							<td class="formtext">Password:</td>
							<td><input type="password" name="pwd"></td>
							<td></td><td><input type="submit" value="Sign In">
						</tr>
						<tr>
						<?php
							if (isset($_GET['logerror']))
							{
								echo "<td colspan='2' style='color:red'>Incorrect username or password.</td>";
							}
							else
							{
								echo "<td colspan='2'>Username or password are incorrect.</td>";
							}
						?>
						</tr>
					</table>
				</form>
			<?php
		  	}
		  ?>
		 	</td>
		</tr>
		<tr>
			<td>
				<a href="register.php" class="option"><strong>Register</strong></a>
				<a href="messages.php" class="option"><strong>Messages</strong></a>
				<a href="adminarea.php" class="option"><strong>Admin Area</strong></a>
			</td>
			<td></td>
		</tr>
	</table>
	<!-- /close main header table -->
</div>
<!-- /close header -->
