<?php
require 'vendor/autoload.php';
session_start();

$api = new SpotifyWebAPI\SpotifyWebAPI();

// Fetch the saved access token from somewhere. A session for example.
$accessToken = $_SESSION["access"];
$refreshToken = $_SESSION["refresh"];

$api->setAccessToken($accessToken);

// It's now possible to request data about the currently authenticated user
$user = $api->me();
//print_r(
 //   $user
//);
$id = $user->id;

// Getting Spotify catalog data is of course also possible
  //$id = $_POST["id"];
  //$pos = $_POST["position"];
  //$pause = $_POST['paused'];
  //$trackURL = "https://play.spotify.com/track/$id";

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
  <title>Kristal Kanta</title>
  <style>
    .nowPlaying {
      font-size: 30px;
      line-height: 36px;
      letter-spacing: .015em;
      text-align: center;
    }
    .songInfo {
      float: center;
    }

    .slidecontainer {
      width: 20%;
    }

    .slider {
      -webkit-appearance: none;
      width: 100%;
      height: 20px;
      background: #808080;
      outline: none;
      opacity: 0.7;
      -webkit-transition: .2s;
      transition: opacity .2s;
    }

    .slider:hover {
      opacity: 1;
    }

    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 20px;
      height: 20px;
      background: #4CAF50;
      cursor: pointer;
    }

    #pause {
      width:48px;
      height:48px;
      border:none;
      background: url(/pauseButton.png) no-repeat;
      background-size: 48px 48px;
      padding:20px;
      margin: 20px auto;
    }

    #play {
      width:48px;
      height:48px;
      border:none;
      background: url(/playButton.png) no-repeat;
      background-size: 48px 48px;
      padding:20px;
      margin: 20px auto;
    }
    .progress {
      color:#fff!important;
      background-color:#4CAF50!important;
    }
  </style>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script>
var player;
var playB;
var pauseB;
var id;
var paused;
var covers = [];
<?php 
  $servername = "localhost";
  $username = "ugs3tvhr6dgsc";
  $password = "Calvo1230";
  $dbname = "dbzr7mz4ubuzdu";
  $playlistTracks = $api->getPlaylistTracks('6CIn6NwaeoiqW3HlKB68Di');

  foreach ($playlistTracks->items as $track) {
    $track = $track->track;
    echo 'covers.push("' . $track->album->images[0]->url . '");';
  }
?>
function play() {
  var playlist = ["https://spotify.crystallizedimagination.com/songs/Mantra.mp3", "https://spotify.crystallizedimagination.com/songs/GoodieBag.mp3", "https://spotify.crystallizedimagination.com/songs/Mariposa.mp3", "https://spotify.crystallizedimagination.com/songs/TelevisionSoFarSoGood.mp3", "https://spotify.crystallizedimagination.com/songs/PruneYouTalkFunny.mp3", "https://spotify.crystallizedimagination.com/songs/Goodmorning.mp3", "https://spotify.crystallizedimagination.com/songs/ThatIMissYou.mp3", "https://spotify.crystallizedimagination.com/songs/SpaceCadet.mp3", "https://spotify.crystallizedimagination.com/songs/WallowsScrawny.mp3", "https://spotify.crystallizedimagination.com/songs/Hooplah.mp3", "https://spotify.crystallizedimagination.com/songs/PleaserWallows.mp3", "https://spotify.crystallizedimagination.com/songs/HowlsMovingCastleTheme.mp3", "https://spotify.crystallizedimagination.com/songs/SummerSnow.mp3"];
  var position = 0;
  var i = 0;
  var name;
  var pausedA;
  player = new Audio(playlist[i]);
  id = "<?php echo $id; ?>";
  player.controls = true;
  var duration;
  var tmp;
  var volC = document.getElementById('volumeContainer');
  //var volV = document.getElementbyId("volume");
  playB = document.getElementById('play');
  pauseB = document.getElementById('pause');
  playB.setAttribute("hidden", "true");
  if (id == "kuzoto") {
    pauseB.removeAttribute("hidden");
  }
  volC.removeAttribute("hidden");
  //volV.setAttribute("value", 25);
  if (id == "kuzoto") {
    $.ajax({
        type: "POST",
        url: "updateCurrentTrack.php",
        data: {'user':id, 'id':i},
        dataType: 'text',
        async: false,
        success: function (response) {
           //Save
        }
    });
    name = $.ajax({
                type: "POST",
                url: "getCurrentTrack.php",
                data: {'id':i+1},
                dataType: 'text',
                async: false,
                success: function (response) {
                  //Save
                }
              }).responseText;
  } else {
            i = $.ajax({
              type: "POST",
              url: "getAdminTrack.php",
              data: {'user':"kuzoto"},
              dataType: 'text',
              async: false,
              success: function (response) {
                //Save
              }
            }).responseText;
            player.src = playlist[i];
    name = $.ajax({
              type: "POST",
              url: "getCurrentTrack.php",
              data: {'id':i+1},
              dataType: 'text',
              async: false,
              success: function (response) {
                //Save
              }
            }).responseText;
  }
  player.addEventListener('play', () => {
    paused = 0;
    if (id == "kuzoto") {
      $.ajax({
          type: "POST",
          url: "updatePauseState.php",
          data: {'user':id, 'paused':paused},
          dataType: 'text',
          async: false,
          success: function (response) {
            //Save
          }
      });
    }
  });
  document.getElementById('songInfo').innerHTML = '<label for="songProgress" class="nowPlaying" id="songName" style="display:block;text-align:center;">' + name + '</label><progress id="songProgress" class="progress-bar bg-success" value="0" max="0"></progress><br>';
  document.getElementById('cover').src = covers[i];
  player.volume = 0.25;
  player.play();
  if (id != "kuzoto") {
    //player.pause();
    tmp = $.ajax({
                type: "POST",
                url: "getPosition.php",
                data: {'id':"kuzoto"},
                dataType: 'text',
                async: false,
                success: function (response) {
                  //Save
                }
              }).responseText;
    player.currentTime = tmp;
    //player.play();
  }
  player.addEventListener('loadeddata', () => {
    duration = player.duration;
  });
  player.addEventListener('ended', () => {
    if (i < playlist.length-1) {
        i++;
        if (id == "kuzoto") {
            $.ajax({
              type: "POST",
              url: "updateCurrentTrack.php",
              data: {'user':id, 'id':i},
              dataType: 'text',
              async: false,
              success: function (response) {
                //Save
              }
            });
        }
            name = $.ajax({
              type: "POST",
              url: "getCurrentTrack.php",
              data: {'id':i+1},
              dataType: 'text',
              async: false,
              success: function (response) {
                //Save
              }
            }).responseText;
        document.getElementById('songName').innerHTML = name;
        document.getElementById('cover').src = covers[i];
        player.src = playlist[i];
        player.play();
    }
  });
  player.addEventListener('durationchange', () => {
    duration = player.duration;
    document.getElementById('songProgress').max = player.duration;
  });
  player.addEventListener('timeupdate', () => {
    position = player.currentTime;
    document.getElementById('songProgress').value = player.currentTime;
    if (id == "kuzoto") {
      $.ajax({
        type: "POST",
        url: "updatePosition.php",
        data: {'position':player.currentTime, 'user':id},
        dataType: 'text',
        async: false,
        success: function (response) {
          //Save
        }
      });
    }
  });
  player.addEventListener('pause', () => {
    paused = 1;
    if (id == "kuzoto") {
      $.ajax({
          type: "POST",
          url: "updatePauseState.php",
          data: {'user':id, 'paused':paused},
          dataType: 'text',
          async: false,
          success: function (response) {
            //Save
          }
      });
    }
  });
  if(id != "kuzoto") {
    setInterval( function() {
      pausedA = $.ajax({
          type: "POST",
          url: "getPauseState.php",
          data: {'user':"kuzoto"},
          dataType: 'text',
          async: false,
          success: function (response) {
            //Save
          }
      }).responseText;
      if(pausedA != paused) {
        if(pausedA == 0) {
          player.play();
        } else if(pausedA == 1) {
          player.pause();
        }
      } 
    }, 100)
  }
}
function SetVolume(val)
    {
        player.volume = val / 100;
        document.getElementById('volumeLabel').innerHTML = "Volume: " + val;
    }
function pause()
    {
      player.pause();
      pauseB.setAttribute("hidden", "true");
      playB.setAttribute("onclick", "resume()"); 
      playB.removeAttribute("hidden");
    }
function resume()
    {
      player.play();
      playB.setAttribute("hidden", "true");
      pauseB.removeAttribute("hidden");
    }
</script>
    <div id="playlistContainer" style="display:flex;flex-direction:column;">
    <img id="cover" style="width:520px;height:520px;margin: 0px auto;">
    <div id="songInfo" style="margin: 0px auto;"></div>
    <button onclick="play()" id="play"></button><button onclick="pause()" id="pause" hidden></button>
    <div class="slidecontainer" id="volumeContainer" style="margin: 0px auto;" hidden>
      <label id="volumeLabel">Volume: 25</label>
      <input type="range" min="0" max="100" value="25" step="1" class="slider" id="volume" oninput="SetVolume(this.value)" onchange="SetVolume(this.value)"></input>
    </div>
    <br>
    <?php
        $servername = "localhost";
        $username = "ugs3tvhr6dgsc";
        $password = "Calvo1230";
        $dbname = "dbzr7mz4ubuzdu";
        $playlistTracks = $api->getPlaylistTracks('6CIn6NwaeoiqW3HlKB68Di');

        foreach ($playlistTracks->items as $track) {
            $track = $track->track;
            echo '<div style="display:flex;align-items:center;background-color:#303030;outline-color:#28a745;outline-radius:2px;margin:2px 0px;"><img src="' . $track->album->images[2]->url . '"><a href="' . $track->external_urls->spotify . '" style="font-size:24px;font-color:#ffffff;">' . $track->name . '</a></div>';
        }
    ?>
    </div>
</body>
</html>