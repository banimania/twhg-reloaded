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
		$sql = "SELECT id FROM users WHERE username = ?";

		if ($stmt = mysqli_prepare($link, $sql)) {
			mysqli_stmt_bind_param($stmt, "s", $param_username);

			$param_username = trim($_POST["username"]);

			if (mysqli_stmt_execute($stmt)) {
      	mysqli_stmt_store_result($stmt);       
        if (mysqli_stmt_num_rows($stmt) == 1) {
          $username_error = "Username already exists";
        } else {
          $username = trim($_POST["username"]);
        }
      }
		}
		mysqli_stmt_close($stmt);
	}

	if (empty(trim($_POST["password"]))) {
  	$password_error = "Password is empty";     
  } elseif (strlen(trim($_POST["password"])) < 6) {
  	$password_error = "Password is too short";
  } elseif (strlen(trim($_POST["password"])) > 16) {
  	$password_error = "Password is too long";
  } else {
  	$password = trim($_POST["password"]);
  }

  $access = 1;
  $deaths = 0;
  $time = 0;
  $score = 0;
  if (empty($username_error) && empty($password_error)) {
    $sql = "INSERT INTO users (id, username, password, access, deaths, time, score) VALUES (DEFAULT, ?, ?, ?, ?, ?, ?)";
    
    if ($stmt = mysqli_prepare($link, $sql)) {
      mysqli_stmt_bind_param($stmt, "ssiidi", $param_username, $param_password, $param_access, $param_deaths, $param_time, $param_score);
      
      $param_username = $username;
      $param_password = password_hash($password, PASSWORD_DEFAULT);
      $param_access = $access;
      $param_deaths = $deaths;
      $param_time = $time;
      $param_score = $score;
      
      mysqli_stmt_execute($stmt);
    }

    mysqli_stmt_close($stmt);
  }
	mysqli_close($link);

	if (empty($username_error) && empty($password_error)) {
		echo("Registered successfully!\n");
	} else {
		echo("Failed registration\n");
	}

	if (!empty($username_error)) {
		echo($username_error . "\n");
	}

	if (!empty($password_error)) {
		echo($password_error . "\n");
	}
}
?>