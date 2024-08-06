<?php
session_start();

require_once 'config.php';

if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
  echo("Not logged in!");
  exit;
}

$besttime = -1;
$deaths = -1;
$sql = "SELECT besttime, deaths FROM levelprogress WHERE levelid = ? AND playerid = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "ii", $_SESSION["id"], $_POST["levelid"]);
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_bind_result($stmt, $time, $death);
    if (mysqli_stmt_fetch($stmt)) {
      $besttime = $time;
      $deaths = $death;
    }
  }
  mysqli_stmt_close($stmt);
}

if ($besttime == -1) {
  echo "N/A N/A";
  exit;
}

echo $besttime . " " . $deaths;
?>
