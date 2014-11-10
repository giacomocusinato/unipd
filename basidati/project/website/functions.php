<?php
	/* Ritorna l'attuale url di base per il server */
	function server_url()
	{
		$server = $_SERVER["SERVER_NAME"];
		if ($server == "localhost")
		{
			return "http://localhost:20080/basidati/~gcusinat/";
		}
		else //($server == "basidati")
		{
			return "http://basidati/basidati/~gcusinat/";
		}
	}
	
	/* Inizia una sessione per autenticare l'utente */
	function login($userinfo)
	{
		$_SESSION['userinfo'] = $userinfo;
	}
	
	/* Autenticazione al database */
	function db_auth()
	{
		$host = "basidati1004.studenti.math.unipd.it";
		$user = "gcusinat";
		$pwd = "LzdSOz8H";
		$conn = mysql_connect($host, $user, $pwd)
			or die($_SERVER['PHP_SELF'] . "Connection failed, plese try again!");
		mysql_select_db("gcusinat-PR", $conn)
			or die ("Could not select gcusinat-PR");
		return $conn;
	}
	
	/* Aggiungo l'utente al database e lo autentico */
	function save_user($username, $password, $email, $conn)
	{
		$date = new DateTime();
		$today = $date->format('Y-m-d');
		$insert_query = "INSERT INTO Users (Username, Pwd, Email, RegDate, PostCount)
										 VALUES ('$username', '$password', '$email', '$today', 0)";
	 	mysql_query($insert_query, $conn)
			or die("Error in adding new user. " . mysql_error($conn));
		mysql_close($conn);
		$userinfo = array (
			"Username" => $username,
			"Pwd" => $password,
			"Email" => $email,
			"RegDate" => $today,
			"PostCount" => 0 
		);
		login($userinfo);
	}
	
	/* Controllo se l'utente e' loggato */
	function is_logged()
	{
		if (isset($_SESSION['userinfo']))
			return true;
		else
			return false;
	}
	
	/* Aggiungo un thread ad una sezione */
	function add_thread($title, $text, $section, $conn)
	{
 		$nthread = mysql_query("SELECT MAX(Id) as Count FROM Threads", $conn)
			or die("Error in creating the thread. " . mysql_error($conn));
		$row = mysql_fetch_assoc($nthread);
		$id = $row['Count'] + 1;
		
		$userinfo = $_SESSION['userinfo'];
		$username = $userinfo['Username'];
		
		$date = new DateTime();
		$today = $date->format('Y-m-d');

		$insert_query = "INSERT INTO Threads (Id, Title, Content, PostDate, Username, SectionName) 
										 VALUES ($id, '$title', '$text', '$today', '$username', '$section')";
	  mysql_query($insert_query, $conn)
	  	or die("Error in creating the thread. " . mysql_error($conn));
		mysql_close($conn);
	}
	
	/* Aggiungo un post ad un thread */
	function add_post($text, $thread_id, $conn)
	{
		$npost = mysql_query("SELECT MAX(Id) as Count FROM Posts", $conn)
			or die("Error in creating the post. " . mysql_error($conn));
		$row = mysql_fetch_assoc($npost);
		$id = $row['Count'] + 1;
		
		$userinfo = $_SESSION['userinfo'];
		$username = $userinfo['Username'];
		
		$date = new DateTime();
		$today = $date->format('Y-m-d');
		
		$insert_query = "INSERT INTO Posts (Id, Content, PostDate, Username, ThreadId) 
						 				 VALUES ($id, '$text', '$today', '$username', '$thread_id')";
		mysql_query($insert_query, $conn)
	  	or die("Error in creating the post. " . mysql_error($conn));
		mysql_close($conn);
	}
	
	/* Aggiungo una conversazione, ritorno l'id per il messaggio iniziale */
	function add_conversation($obj, $receivers, $conn)
	{
		$nconv = mysql_query("SELECT MAX(Id) as Count FROM Conversations", $conn)
			or die("Error in creating the post. " . mysql_error($conn));
		$row = mysql_fetch_assoc($nconv);
		$id = $row['Count'] + 1;
		
		mysql_query("INSERT INTO Conversations (Id, Obj) VALUES ($id, '$obj')", $conn)
	  	or die("Error in creating the conversation. " . mysql_error($conn));
	  
	  /* Aggiungo i valori alla tabella UserConversation */
		$userinfo = $_SESSION['userinfo'];
		$username = $userinfo['Username'];
		
		mysql_query("INSERT INTO UserConversation (Username, Id) VALUES ('$username', '$id')", $conn)
	  	or die("Error in creating the conversation. " . mysql_error($conn));
	  	
	  foreach ($receivers as $value)
	  {
			mysql_query("INSERT INTO UserConversation (Username, Id) VALUES ('$value', '$id')", $conn)
	  		or die("Error in creating the conversation. " . mysql_error($conn));
	  }
	  
	  return $id;
	}
	
	/* Aggiungo un messaggio alla conversazione */
	function add_message($content, $convid, $conn)
	{
		$nmess = mysql_query("SELECT MAX(Id) as Count FROM Messages", $conn)
			or die("Error in creating the post. " . mysql_error($conn));
		$row = mysql_fetch_assoc($nmess);
		$id = $row['Count'] + 1;
		
		$userinfo = $_SESSION['userinfo'];
		$username = $userinfo['Username'];
		
		$date = new DateTime();
		$today = $date->format('Y-m-d');
		
		mysql_query("INSERT INTO Messages (Id, Content, PostDate, Username, Conversation) VALUES ($id, '$content', '$today', '$username', '$convid')", $conn)
	  	or die("Error in creating the message. " . mysql_error($conn));
	}
	
	/* Controlla se i mittenti esistono */
	function receivers_exists($receivers, $conn)
	{
	  foreach ($receivers as $value)
	  {
			$user = mysql_query("SELECT * FROM Users WHERE Username='$value'", $conn)
				or die("Operation failed." . mysql_error($conn));
			if ($row = mysql_fetch_assoc($user))
			{
			
			}
			else
			{
				return false;
			}		
	  }
	  return true;
	}
	
  /* Controlla se l'utente loggato e' un mod */
  function is_mod()
  {
		$userinfo = $_SESSION['userinfo'];
		$username = $userinfo['Username'];
		
		$conn = db_auth();
		
		$mod = mysql_query("SELECT * FROM Moderators WHERE Username='$username'", $conn);
		if ($row = mysql_fetch_assoc($mod))
		{
			return true;
		}
		else
		{
			$admin = mysql_query("SELECT * FROM Admins WHERE Username='$username'", $conn);
			if ($row = mysql_fetch_assoc($admin))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
  }
  
  /* Controlla se l'utente loggato e' un admin */
  function is_admin()
  {
  	if (!is_logged())
  	{
  		return false;
  	}
  	
		$userinfo = $_SESSION['userinfo'];
		$username = $userinfo['Username'];
		
		$conn = db_auth();
		
		$admin = mysql_query("SELECT * FROM Admins WHERE Username='$username'", $conn);
		if ($row = mysql_fetch_assoc($admin))
		{
			return true;
		}
		else
		{
			return false;
		}
  }
  
  /* Ritorna il nome della sezione dato l-id del thread */
  function get_section($id, $conn)
  {
  	$section = mysql_query("SELECT * FROM Threads WHERE Id=$id", $conn);
  	if ($row = mysql_fetch_assoc($section))
  	{
  		$name = $row['SectionName'];
  		return $name;
  	}
  }
  
  /* Aggiorna i valori di un thread */
  function update_thread($title, $text, $id, $conn)
  {
  	mysql_query("UPDATE Threads SET Title='$title', Content='$text' WHERE Id='$id'", $conn);
  }
  
  /* Ottiene il thread padre del post */
  function get_thread($id, $conn)
  {
  	$thread = mysql_query("SELECT * FROM Posts WHERE Id=$id", $conn);
  	if ($row = mysql_fetch_assoc($thread))
  	{
  		$thread_id = $row['ThreadId'];
  		return $thread_id;
  	}
  }
  
  /* Controlla se esiste una sezione con un dato nome */
  function is_section($name, $conn)
  {
  	$section = mysql_query("SELECT * FROM Sections WHERE Name='$name'", $conn);
  	if ($row = mysql_fetch_assoc($section))
  	{
  		if ($row['Name'] == $name)
  			return true;
  		else
  			return false;
  	}
  	return false;
  }
  
  /* Controlla se esiste un utente con un dato username */
  function is_user($name, $conn)
  {
  	$user = mysql_query("SELECT * FROM Users WHERE Username='$name'", $conn);
  	if ($row = mysql_fetch_assoc($user))
  	{
  		if ($row['Username'] == $name)
  			return true;
  		else
  			return false;
  	}
  	return false;
  }
  
  /* Ottiene il post count di un utente */
  function post_count($username)
  {
  	$conn = db_auth();
  	$user = mysql_query("SELECT * FROM Users WHERE Username='$username'", $conn);
  	if ($row = mysql_fetch_assoc($user))
  	{
  		$count = $row['PostCount'];
			return $count;
  	}
  	return false;
  }
?>
