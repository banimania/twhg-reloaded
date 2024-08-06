<?php
session_start();

header('Content-type: text/plain');

require_once 'config.php';

$sql = "SELECT username, deaths, time, score FROM users ORDER BY score DESC LIMIT 10";

if($stmt = mysqli_prepare($link, $sql)) {
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_store_result($stmt);
    if(mysqli_stmt_num_rows($stmt) > 0) {
      mysqli_stmt_bind_result($stmt, $username, $deaths, $time, $score);
      while(mysqli_stmt_fetch($stmt)) {
        echo($username . " " . $deaths . " " . $time . " " . $score . "\n");
      }
    }
  }
}
?>
