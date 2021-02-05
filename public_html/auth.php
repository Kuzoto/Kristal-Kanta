<?php
require 'vendor/autoload.php';
session_start();

$session = new SpotifyWebAPI\Session(
    '352f0c2d4a4e4af686074a32b8bcbcf0',
    '0d521abe30be4834b522f7bee81fc805',
    'https://spotify.crystallizedimagination.com/callback.php'
);

$state = $session->generateState();
$_SESSION['storedState'] = $state;

$options = [
    'scope' => [
        'playlist-read-private',
        'user-read-private',
        'user-modify-playback-state',
        'user-read-playback-position',
        'playlist-read-collaborative',
        'user-read-currently-playing',
        'user-read-playback-state',
        'user-read-recently-played',
    ],
    'state' => $state,
];

header('Location: ' . $session->getAuthorizeUrl($options));
die();
?>