<?php
	require 'functions.php';
	
	/* Url corretto del server per il redirecting */
	$server_url = server_url();
	
	/* Autenticazione al database */	
	$conn = db_auth();
	
	/* Inizio la sessione per verificare i dati dell'utente */
	session_start();
	
	/* Controllo logout */
	if (isset($_GET['logout']))
	{
		unset($_SESSION["userinfo"]);
		header("Location:" . $_SERVER['HTTP_REFERER']);
	}
	/* Controllo login */
	else if (isset($_GET['login']))
	{
		$password = $_POST['pwd'];	
		$username = $_POST['username'];
		
		/* Interrego il database e controllo l'esistenza dell'utente */
		$user = mysql_query("SELECT * FROM Users WHERE Username='$username'", $conn)
		or die("Authentication failed. " . mysql_error($conn));
		
		if ($row = mysql_fetch_assoc($user))
		{
			/* L'utente esiste, controllo la password */
			if ($password == $row['Pwd'])
			{
				/* Dati corretti, autentico l'utente */				
				login($row);
				header("Location:" . $_SERVER['HTTP_REFERER']);
				exit;
			}
			else
			{
				/* Password errata */
				header("Location:" . $server_url . "home.php?logerror=true");
				exit;
			}
		}
		else
		{
			/* L'utente non esiste */
			header("Location:" . $server_url . "home.php?logerror=true");
			exit;
		}
		
	}
	/* Controllo registrazione */
	else if (isset($_GET['reg']))
	{	
		/* Ottieni i valori in POST */
		$password = $_POST['pwd1'];	
		$passwordCheck = $_POST['pwd2'];
		$username = $_POST['username'];
		$email = $_POST['email'];
	
		/* Controlla che i campi non siano vuoti */
		if ($password == "" || $username == "" || $email == "")
		{
			header("Location:" . $server_url . "register.php?m=empty");
			exit;
		}

		/* Controllo della password  */
		if ($password != $passwordCheck)
		{
			header("Location:" . $server_url . "register.php?m=password");
			exit;
		}
		/* Controllo unicita' username ed email */
		$users = mysql_query("SELECT * FROM Users", $conn)
			or die("Operation failed." . mysql_error($conn));
		while ($row = mysql_fetch_assoc($users))
		{
			if ($username == $row['Username'])
			{
				header("Location:" . $server_url . "register.php?m=username");
				exit;
			}
			if ($email == $row['Email'])
			{
				header("Location:" . $server_url . "register.php?m=email");
				exit;
			}
		}		
		/* Aggiungo l'utente al database e lo autentico */
		save_user($username, $password, $email, $conn);
		header("Location:" . $server_url . "home.php");
		exit;
	}
	/* Processo il nuovo thread */
	else if (isset($_GET['newthread']))
	{
		$section = $_GET['sec'];
		/* Se il titolo risulta vuoto, errore */
		if (empty($_POST['title']))
		{
			header("Location:" . $server_url . "newthread.php?sec=$section&empty=true");
			exit;
		}
		$title = mysql_real_escape_string($_POST['title']);
		$text = mysql_real_escape_string($_POST['text']);
		add_thread($title, $text, $section, $conn);
		header("Location:" . $server_url . "section.php?title=$section");
		exit;
	}
	/* Processo il nuovo post */
	else if (isset($_GET['newpost']))
	{
		$text = mysql_real_escape_string($_POST['text']);
		$id = $_GET['id'];
		/* Se il testo risulta vuoto, errore */
		if (empty($_POST['text']))
		{
			header("Location:" . $server_url . "thread.php?id=$id&empty=true");
			exit;
		}
		add_post($text, $id, $conn);
		header("Location:" . $server_url . "thread.php?id=$id");
		exit;
	}
	/* Processo la nuova conversazione */
	else if (isset($_GET['newconv']))
	{
		$receivers_str = $_POST['receivers'];
		$receivers = explode(",", $receivers_str);
		if (empty($receivers) || !receivers_exists($receivers, $conn))
		{
			header("Location:" . $server_url . "newconversation.php?receivers=true");
			exit;
		}
		$obj = mysql_real_escape_string($_POST['object']);
		$text = mysql_real_escape_string($_POST['text']);
		if (empty($obj) || empty($text))
		{
			header("Location:" . $server_url . "newconversation.php?empty=true");
			exit;
		}
		
		$id = add_conversation($obj, $receivers, $conn);
		add_message($text, $id, $conn);
		header("Location:" . $server_url . "conversation.php?id=$id");
		exit;
	}
	/* Processo il nuovo messaggio */
	else if (isset($_GET['newmess']))
	{
		$text = mysql_real_escape_string($_POST['text']);
		$id = $_GET['id'];
		add_message($text, $id, $conn);
		header("Location:" . $server_url . "conversation.php?id=$id");
		exit;
	}
	/* Inizializza l'update o delete del thread */
	else if (isset($_GET['managethread']))
	{
		$id = $_GET['id'];
  	$sec = get_section($id, $conn);
		if ($_POST['action'] == 'Delete')
		{
	  	mysql_query("DELETE FROM Threads WHERE Id='$id'", $conn);
			header("Location:" . $server_url . "section.php?title=$sec&id=$id");
			exit;
		}
		else
		{
			header("Location:" . $server_url . "edit.php?thread=$id");
			exit;
		}
	}
	/* Processo il thread modificato */
	else if (isset($_GET['modthread']))
	{
		$id = $_GET['id'];
  	$sec = get_section($id, $conn);
		/* Se il titolo risulta vuoto, errore */
		if (empty($_POST['title']))
		{
			header("Location:" . $server_url . "edit.php?thread=$id&empty=true");
			exit;
		}
		$title = mysql_real_escape_string($_POST['title']);
		$text = mysql_real_escape_string($_POST['text']);
		update_thread($title, $text, $id, $conn);
		header("Location:" . $server_url . "thread.php?id=$id");
		exit;
	}
	/* Inizializza l'update o delete del post */
	else if (isset($_GET['managepost']))
	{
		$id = $_GET['id'];
  	$thread_id = get_thread($id, $conn);
		if ($_POST['action'] == 'Delete')
		{
	  	mysql_query("DELETE FROM Posts WHERE Id='$id'", $conn);
			header("Location:" . $server_url . "thread.php?id=$thread_id");
			exit;
		}
		else
		{
			header("Location:" . $server_url . "edit.php?post=$id");
			exit;
		}
	}
	/* Processo il post modificato */
	else if (isset($_GET['modpost']))
	{
		$id = $_GET['id'];
  	$thread_id = get_thread($id, $conn);
		/* Se il titolo risulta vuoto, errore */
		if (empty($_POST['text']))
		{
			header("Location:" . $server_url . "edit.php?post=$id&empty=true");
			exit;
		}
		$text = mysql_real_escape_string($_POST['text']);
  	mysql_query("UPDATE Posts SET Content='$text' WHERE Id='$id'", $conn);
		header("Location:" . $server_url . "thread.php?id=$thread_id");
		exit;
	}
	/* Inizializzo update o delete di sezioni ed utenti, Admin area */
	else if (isset($_GET['adminarea']))
	{
		$name = $_POST['name'];
		if ($_POST['action'] == 'delete')
		{
			if ($_POST['object'] == 'section')
			{
			  /* Delete sezione */
				if (is_section($name, $conn))
				{
					mysql_query("DELETE FROM Sections WHERE Name='$name'", $conn);
					header("Location:" . $server_url . "adminarea.php?secdel=true");
					exit;
				}
				else
				{
					header("Location:" . $server_url . "adminarea.php?nosec=true");
					exit;
				}
			}
			else
			{
				/* Delete user */
				if (is_user($name, $conn))
				{
					mysql_query("DELETE FROM Users WHERE Username='$name'", $conn);
					header("Location:" . $server_url . "adminarea.php?usrdel=true");
					exit;
				}
				else
				{
					header("Location:" . $server_url . "adminarea.php?nousr=true");
					exit;
				}
			}		
		}
		else
		{
			if ($_POST['object'] == 'section')
			{
			  /* Update sezione */
				if (is_section($name, $conn))
				{
					header("Location:" . $server_url . "edit.php?section=$name");
					exit;
				}
				else
				{
					header("Location:" . $server_url . "adminarea.php?nosec=true");
					exit;
				}
			}
			else
			{
				/* Update user */
				if (is_user($name, $conn))
				{
					header("Location:" . $server_url . "edit.php?user=$name");
					exit;
				}
				else
				{
					header("Location:" . $server_url . "adminarea.php?nousr=true");
					exit;
				}
			}		
		}	
	}
	/* Processo la sezione modificata */
	else if (isset($_GET['modsec']))
	{
		$name = $_GET['name'];
		/* Se il titolo risulta vuoto, errore */
		if (empty($_POST['title']))
		{
			header("Location:" . $server_url . "edit.php?section=$name&empty=true");
			exit;
		}
		$title = mysql_real_escape_string($_POST['title']);
		$description = mysql_real_escape_string($_POST['description']);
  	mysql_query("UPDATE Sections SET Name='$title', Description='$description' WHERE Name='$name'", $conn);
		header("Location:" . $server_url . "home.php");
		exit;
	}
	/* Processo l'username modificato */
	else if (isset($_GET['modusr']))
	{
		$name = $_GET['username'];
		/* Se vuoto, errore */
		if (empty($_POST['username']))
		{
			header("Location:" . $server_url . "edit.php?user=$name&empty=true");
			exit;
		}
		$username = $_POST['username'];
		/* Controllo se esiste gia' */
		$user = mysql_query("SELECT * FROM Users WHERE Username='$username'", $conn)
			or die("Operation failed." . mysql_error($conn));
		if ($row = mysql_fetch_assoc($user))
		{
			if ($username == $row['Username'])
			{
				header("Location:" . $server_url . "edit.php?user=$name&exist=true");
				exit;
			}
		}
		else
		{
			mysql_query("UPDATE Users SET Username='$username' WHERE Username='$name'", $conn);
			header("Location:" . $server_url . "adminarea.php?usrup=true");
			exit;
		}
	}
?>

