<?php

require_once 'config.php';

$levelid = $_POST["levelid"];

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
	echo "N/A";
	exit();
}

echo $dif;

?>