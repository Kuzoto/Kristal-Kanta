<?php
$servername = "localhost";
$username = "ugs3tvhr6dgsc";
$password = "Calvo1230";
$dbname = "dbzr7mz4ubuzdu";

$conn = new mysqli($servername, $username, $password, $dbname);
          // Check connection
          if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
          }
            $current_track = $_POST["id"]; 
            $sql = "SELECT `duration` FROM `playlist` WHERE `id` = ?";

            $stmt = $conn->prepare($sql);
            $stmt->bind_param("i", $current_track);
            $stmt->bind_result($duration);
            $stmt->execute();
            if ($stmt->fetch()) {
              echo $duration;
            }
            $stmt->close();
            //sleep($duration);
            $conn->close();
?>