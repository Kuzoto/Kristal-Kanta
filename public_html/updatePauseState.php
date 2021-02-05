<?php
$servername = "localhost";
$username = "ugs3tvhr6dgsc";
$password = "Calvo1230";
$dbname = "dbzr7mz4ubuzdu";

$user = $_POST['user'];
$pause = $_POST['paused'];

$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}


$sql = "UPDATE `admins` SET `paused`=? WHERE `username`=?";

$stmt = $conn->prepare($sql);
$stmt->bind_param("is", $pause, $user);
$stmt->execute();

$stmt->close();
$conn->close();
?>