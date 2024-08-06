<?php
session_start();

require_once 'config.php';

$username = "";
$password = "";

$username_error = "";
$password_error = "";

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	if (empty(trim($_POST["username"]))) {
		$username_error = "Username is empty";
	} else {
		$username = trim($_POST["username"]);
	}

	if (empty(trim($_POST["password"]))) {
		$password_error = "Password is empty";
	} else {
		$password = trim($_POST["password"]);
	}

	if (empty($username_error) && empty($password_error)) {
		$sql = "SELECT id, username, password, access, deaths, time, score FROM users WHERE username = ?";
		if($stmt = mysqli_prepare($link, $sql)) {
			mysqli_stmt_bind_param($stmt, "s", $username);

			if(mysqli_stmt_execute($stmt)) {
				mysqli_stmt_store_result($stmt);

				if(mysqli_stmt_num_rows($stmt) == 1) {
					mysqli_stmt_bind_result($stmt, $id, $username, $hashed_password, $access, $deaths, $time, $score);
					if (mysqli_stmt_fetch($stmt)) {
						if (password_verify($password, $hashed_password))  {
							session_start();
                            
				            $_SESSION["loggedin"] = true;
				            $_SESSION["id"] = $id;
				            $_SESSION["username"] = $username;   
				            $_SESSION["access"] = $access;
				            $_SESSION["deaths"] = $deaths;
				            $_SESSION["time"] = $time;
				            $_SESSION["score"] = $score;
						} else {
							$password_error = "Incorrect password";
						}
					}
				} else {
					$username_error = "Username has not been registered";
				}
			}
		}

		mysqli_stmt_close($stmt);
	}
	mysqli_close($link);

	if(isset($_SESSION["loggedin"]) && $_SESSION["loggedin"] === true){
	  echo("Logged in successfully!\n");
	} else {
		echo("Login failed\n");
	}

	if (!empty($username_error)) {
		echo($username_error . "\n");
	}

	if (!empty($password_error)) {
		echo($password_error . "\n");
	}
}

?>