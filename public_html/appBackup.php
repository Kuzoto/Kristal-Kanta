<?php
require 'vendor/autoload.php';
session_start();

$api = new SpotifyWebAPI\SpotifyWebAPI();

// Fetch the saved access token from somewhere. A session for example.
$accessToken = $_SESSION["access"];
$refreshToken = $_SESSION["refresh"];

$api->setAccessToken($accessToken);

// It's now possible to request data about the currently authenticated user
print_r(
    $api->me()
);

// Getting Spotify catalog data is of course also possible
  $id = $_POST["id"];
  $pos = $_POST["position"];
  $pause = $_POST['paused'];
  $trackURL = "https://play.spotify.com/track/$id";

  //if ($id != null and $pos != null) {
  //} 

//if($_POST["submit"]) {
    //$upload_folder="uploads/"
    //$email=$_POST["email"];
    //$user=$_POST["name"];
    //$password=$_POST["password"];
    //$position=0;
    //$current_track=1;

?>
<!DOCTYPE html>
<html>
<head>
  <title>Spotify Web Playback SDK Quick Start Tutorial</title>
</head>
<body>
    <h1>Spotify Web Playback API Quick Start Tutorial</h1>
    <h2>Open your console log: <code>View > Developer > JavaScript Console</code></h2>
    <?php
        $servername = "localhost";
        $username = "ugs3tvhr6dgsc";
        $password = "Calvo1230";
        $dbname = "dbzr7mz4ubuzdu";
        $playlistTracks = $api->getPlaylistTracks('6CIn6NwaeoiqW3HlKB68Di');

        foreach ($playlistTracks->items as $track) {
            $track = $track->track;
            echo '<a href="' . $track->external_urls->spotify . '">' . $track->name . '</a> <br>';
        }
        foreach ($playlistTracks->items as $track) {
          $conn = new mysqli($servername, $username, $password, $dbname);
          // Check connection
          if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
          }
            $track = $track->track;
            $name = $track->name;
            $album = $track->album->name;
            $duration = round($track->duration_ms / 1000);
            $duration = intval($duration); 
            $sql = "SELECT count(`album`) FROM `playlist` WHERE `track` = ?";

            $stmt = $conn->prepare($sql);
            $stmt->bind_param("s", $name);
            $stmt->bind_result($count);
            $stmt->execute();
            $stmt->close();

            if ($count > 0) {
              echo "repeated track";
            } else {
              $sql = "INSERT INTO `playlist` (`track`, `album`, `duration`) VALUES(?, ?, ?)";

              $stmt = $conn->prepare($sql);
              $stmt->bind_param("ssi", $name, $album, $duration);
              $stmt->execute();
              $stmt->close();
            }
            //sleep($duration);
            $conn->close();
        }
    ?>
</body>
</html>