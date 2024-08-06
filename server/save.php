<?php
session_start();

require_once 'config.php';

if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
  echo("Not logged in!");
  exit;
}

if (!isset($_POST['deaths']) || !isset($_POST['time']) || !isset($_POST['score'])) {
  echo("Incomplete data");
  exit;
}

$deaths = $_POST['deaths'];
$time = $_POST['time'];
$score = $_POST['score'];

$sql = "UPDATE users SET deaths = ?, time = ?, score = ? WHERE id = ?";

if ($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "idii", $deaths, $time, $score, $_SESSION["id"]);

  if (mysqli_stmt_execute($stmt)) {
    echo "Saved successfully!";
    $_SESSION["deaths"] = $deaths;
    $_SESSION["time"] = $time;
    $_SESSION["score"] = $score;
  }

  mysqli_stmt_close($stmt);
}

mysqli_close($link);
?>