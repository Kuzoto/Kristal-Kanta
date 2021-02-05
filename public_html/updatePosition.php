<?php
$servername = "localhost";
$username = "ugs3tvhr6dgsc";
$password = "Calvo1230";
$dbname = "dbzr7mz4ubuzdu";

$user = $_POST['user'];
$position = $_POST['position'];
$position = doubleval($position);
//if(!is_string($position)) {
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}


$sql = "UPDATE `admins` SET `position`=? WHERE `username`=?";

$stmt = $conn->prepare($sql);
$stmt->bind_param("is", $position, $user);
$stmt->execute();

$stmt->close();
$conn->close();
//}
?>