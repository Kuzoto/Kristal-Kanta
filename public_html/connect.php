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
  #$track = $api->getTrack('7EjyzZcbLxW7PaaLua9Ksb');
?>
<!DOCTYPE html>
<html>
<head>
  <title>Spotify Web Playback SDK Quick Start Tutorial</title>
</head>
<body>
    <h1>Spotify Web Playback SDK Quick Start Tutorial</h1>
    <h2>Open your console log: <code>View > Developer > JavaScript Console</code></h2>

    <script src="https://sdk.scdn.co/spotify-player.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script>
        window.onSpotifyWebPlaybackSDKReady = () => {
        const token = "<?php echo $accessToken; ?>";
        const player = new Spotify.Player({
            name: 'Web Playback SDK Quick Start Player',
            getOAuthToken: cb => { cb(token); }
        });
        const play = ({
            spotify_uri,
            playerInstance: {
                _options: {
                getOAuthToken,
                id
                }
            }
        }) => {
            getOAuthToken(access_token => {
                fetch(`https://api.spotify.com/v1/me/player/play?device_id=${id}`, {
                    method: 'PUT',
                    body: JSON.stringify({ uris: [spotify_uri] }),
                    headers: {
                        'Content-Type': 'application/json',
                        'Authorization': `Bearer ${access_token}`
                    },
                });
            });
        };
        // Error handling
        player.addListener('initialization_error', ({ message }) => { console.error(message); });
        player.addListener('authentication_error', ({ message }) => { console.error(message); });
        player.addListener('account_error', ({ message }) => { console.error(message); });
        player.addListener('playback_error', ({ message }) => { console.error(message); });

        // Playback status updates
        player.addListener('player_state_changed', ({track_window: { current_track }, state, paused }) => { 
          /*$.ajax({
            url: "app.php",
            type: "POST",
            data: {'id': current_track, 'position': position, 'paused': paused},
            success:function(data) {}
          });*/
          console.log(current_track);
        });

        // Ready
        player.addListener('ready', ({ device_id }) => {
            console.log('Ready with Device ID', device_id);
        });

        // Not Ready
        player.addListener('not_ready', ({ device_id }) => {
            console.log('Device ID has gone offline', device_id);
        });

        // Connect to the player!
        player.connect();
        };
    </script>
</body>
</html>