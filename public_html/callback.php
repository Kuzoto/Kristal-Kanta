<?php
require 'vendor/autoload.php';
session_start();

$session = new SpotifyWebAPI\Session(
    '352f0c2d4a4e4af686074a32b8bcbcf0',
    '0d521abe30be4834b522f7bee81fc805',
    'https://spotify.crystallizedimagination.com/callback.php'
);

$state = $_GET['state'];
$storedState = $_SESSION['storedState'];
// Fetch the stored state value from somewhere. A session for example

if ($state !== $storedState) {
    // The state returned isn't the same as the one we've stored, we shouldn't continue
    die('State mismatch');
}

// Request a access token using the code from Spotify
$session->requestAccessToken($_GET['code']);

$accessToken = $session->getAccessToken();
$refreshToken = $session->getRefreshToken();

// Store the access and refresh tokens somewhere. In a session for example
$_SESSION["access"] = $accessToken;
$_SESSION["refresh"] = $refreshToken;
// Send the user along and fetch some data!
header('Location: app.php');
die();
?>