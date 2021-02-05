<?php
$servername = "localhost";
$username = "ugs3tvhr6dgsc";
$password = "Calvo1230";
$dbname = "dbzr7mz4ubuzdu";

$user = $_POST["user"];

mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$sql = "SELECT `paused` FROM `admins` WHERE `username` = ?";

$stmt = $conn->prepare($sql);
$stmt->bind_param("s", $user);
$stmt->execute();
$stmt->store_result();
$stmt->bind_result($pause);
if ($stmt->fetch()) {
  echo $pause;
}
$stmt->close();
$conn->close();
?>