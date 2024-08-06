<?php
session_start();

require_once 'config.php';

if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
  echo("Not logged in!");
  exit;
}

$scorecalc = 0;
$sql = "SELECT SUM(scoregiven) FROM levelprogress WHERE playerid = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "i", $_SESSION["id"]);
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_bind_result($stmt, $sumscore);
    if (mysqli_stmt_fetch($stmt)) {
      if ($sumscore != null) $scorecalc = $sumscore;
    }
  }
  mysqli_stmt_close($stmt);
}

$sql = "UPDATE users SET score = ? WHERE id = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "ii", $scorecalc, $_SESSION["id"]);
  mysqli_stmt_execute($stmt);
  mysqli_stmt_close($stmt);
}

$deathcalc = 0;
$sql = "SELECT SUM(deaths) FROM levelprogress WHERE playerid = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "i", $_SESSION["id"]);
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_bind_result($stmt, $sumdeaths);
    if (mysqli_stmt_fetch($stmt)) {
      if ($sumdeaths != null) $deathcalc = $sumdeaths;
    }
  }
  mysqli_stmt_close($stmt);
}

$sql = "UPDATE users SET deaths = ? WHERE id = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "ii", $deathcalc, $_SESSION["id"]);
  mysqli_stmt_execute($stmt);
  mysqli_stmt_close($stmt);
}

$sql = "SELECT id, username, password, access, deaths, time, score FROM users WHERE id = ?";
if($stmt = mysqli_prepare($link, $sql)) {
  mysqli_stmt_bind_param($stmt, "i", $_SESSION["id"]);
  if(mysqli_stmt_execute($stmt)) {
    mysqli_stmt_store_result($stmt);

    if(mysqli_stmt_num_rows($stmt) == 1) {
      mysqli_stmt_bind_result($stmt, $id, $username, $hashed_password, $access, $deaths, $time, $score);
      if (mysqli_stmt_fetch($stmt)) {
        $_SESSION["loggedin"] = true;
        $_SESSION["id"] = $id;
        $_SESSION["username"] = $username;   
        $_SESSION["access"] = $access;
        $_SESSION["deaths"] = $deaths;
        $_SESSION["time"] = $time;
        $_SESSION["score"] = $score;
      }
    }
  }
}

echo($_SESSION["id"] . "\n" . $_SESSION["username"] . "\n" . $_SESSION["access"] . "\n" . $_SESSION["deaths"] . "\n" . $_SESSION["time"] . "\n" . $_SESSION["score"]);
?>
