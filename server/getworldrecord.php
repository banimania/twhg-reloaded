<?php
session_start();

require_once 'config.php';

$playerid = -1;
$besttime = -1;

$sql = "SELECT playerid, besttime FROM levelprogress WHERE levelid = ? ORDER BY scoregiven DESC LIMIT 1";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "i", $_POST["levelid"]);
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_bind_result($stmt, $pid, $time);
    if (mysqli_stmt_fetch($stmt)) {
      $playerid = $pid;
      $besttime = $time;
    }
  }
  mysqli_stmt_close($stmt);
}

$username = "";

$sql = "SELECT username FROM users WHERE id = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "i", $playerid);
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_store_result($stmt);

    if(mysqli_stmt_num_rows($stmt) == 1) {
      mysqli_stmt_bind_result($stmt, $user);
      if (mysqli_stmt_fetch($stmt)) {
        $username = $user;
      }
    }
  }
}

if ($besttime == -1 || empty($username)) {
  echo "N/A";
  exit;
}

echo $besttime . " by " . $username;
?>
