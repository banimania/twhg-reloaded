<?php
session_start();

require_once 'config.php';

if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
  echo("Could not submit score: Not logged in!");
  exit;
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	$levelid = $_POST["levelid"];
	$playerid = $_SESSION["id"];
	$besttime = $_POST["besttime"];
	$deaths = $_POST["deaths"];

	if (empty(trim($levelid))) {
		echo "Level id is empty";
		exit;
	}

	if (is_float($besttime)) {
		echo "Best time is empty";
		exit;
	}

	if (is_int($deaths)) {
		echo "Deaths is empty";
		exit;
	}

	$dif = -1;
	$sql = "SELECT difficulty FROM levels WHERE id = ?";
	if ($stmt = mysqli_prepare($link, $sql)) {
		mysqli_stmt_bind_param($stmt, "i", $levelid);
		if (mysqli_stmt_execute($stmt)) {
      mysqli_stmt_store_result($stmt);       
      if(mysqli_stmt_num_rows($stmt) == 1) {
				mysqli_stmt_bind_result($stmt, $difficulty);
				if (mysqli_stmt_fetch($stmt)) {
					$dif = $difficulty;
				}
			}
		}
		mysqli_stmt_close($stmt);
	}

	if ($dif == -1) {
		echo "Could not submit level: Could not find level";
		exit();
	}

	$score = floor(1000 * (($dif * $dif) / ($besttime + 1)));
	$scorewon = 0;

	$submit = true;

	$sql = "SELECT scoregiven FROM levelprogress WHERE playerid = ? AND levelid = ?";
	if ($stmt = mysqli_prepare($link, $sql)) {
		mysqli_stmt_bind_param($stmt, "ii", $playerid, $levelid);
		if (mysqli_stmt_execute($stmt)) {
      mysqli_stmt_store_result($stmt);       
      if(mysqli_stmt_num_rows($stmt) == 1) {
				mysqli_stmt_bind_result($stmt, $scoregiven);
				if (mysqli_stmt_fetch($stmt)) {
					if ($score >= $scoregiven) {
						$submit = true;
						$scorewon = $score - $scoregiven;
					} else {
						$submit = false;
					}
				}
			} else {
				$scorewon = $score;
			}
		}
		mysqli_stmt_close($stmt);
	}

	if (!$submit) {
		echo "Score not submitted: You did not get a better score";
		return;
	}

	$sql = "DELETE FROM levelprogress WHERE playerid = ? AND levelid = ?";
	if ($stmt = mysqli_prepare($link, $sql)) {
		mysqli_stmt_bind_param($stmt, "ii", $playerid, $levelid);
		mysqli_stmt_execute($stmt);
		mysqli_stmt_close($stmt);
	}

	$sql = "INSERT INTO levelprogress (playerid, levelid, besttime, scoregiven, deaths) VALUES (?, ?, ?, ?, ?)";
	if ($stmt = mysqli_prepare($link, $sql)) {
     mysqli_stmt_bind_param($stmt, "iidii", $playerid, $levelid, $besttime, $score, $deaths);
     
     mysqli_stmt_execute($stmt);
     mysqli_stmt_close($stmt);
   }


	echo "Submitted a score of " . $score . "! (won " . $scorewon . ")";
}
?>