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

if($_POST["submit"]) {
    //$upload_folder="uploads/"
    $email=$_POST["email"];
    $user=$_POST["name"];
    $hash_password=password_hash($_POST["password"], PASSWORD_DEFAULT);
    $position=0;
    $current_track=1;

    $sql = "SELECT count(`username`) FROM `admins` WHERE `email` = ?";

    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $email);
    $stmt->bind_result($count);
    $stmt->execute();
    $stmt->close();

    if ($count > 0) {
      echo "repeated email";
    } else {
        $sql = "INSERT INTO `admins` (`email`, `username`, `hash_password`, `position`, `current_track`) VALUES(?, ?, ?, ?, ?)";

        $stmt = $conn->prepare($sql);
        $stmt->bind_param("sssii", $email, $user, $hash_password, $position, $current_track);
        $stmt->execute();
        $stmt->close();
    }
    $conn->close();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
<style>
body {
    background-image: url("https://crystallizedimagination.com/vexlorespot.png");
    background-size: cover;
    background-repeat: no-repeat;
    position: fixed;
    overflow: hidden;
    width: 100%;
}
.shopping-cart {
  width: 500px;
  height: 450px;
  margin: 80px auto;
  background: #FFFFFF;
  box-shadow: 1px 2px 3px 0px rgba(0,0,0,0.10);
  border-radius: 6px;
 
  display: flex;
  flex-direction: column;
}
.navbar {
    overflow: hidden;
    float: center;
    background-color: white;
    padding: 0px 20px;
    color: black;
    height: 300px;
}
.navbar p {
  float: center;
  text-align: center;
  padding: 12px;
  text-decoration: none;
  font-size: 18px; 
  line-height: 18px;
  border-radius: 0px;
  color:black;
  border: 0;
  border-radius: 0;
  margin-bottom: 0;
}
</style>
<meta charset="utf-8">
<title>Create User</title>
</head>
<body>
<div class="shopping-cart">
<p>Info<p><br>
<form  method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" enctype="multipart/form-data">
<label>Username(Required):</label><input type="Name" name="name"><br>
<label>Email(Required):</label><input type="Name" name="email"><br>
<label>Password(Required):</label><input type="Name" name="password"><br>
  <input type="submit" name="submit"><br>
</form><br>
<a href="https://crystallizedimagination.com">Home</a>
</div>
</body>
</html>