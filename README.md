Kristal Kanta

Video Demo: https://youtu.be/V2vciClMcgE

Description:

This web-application, currently called Kristal Kanta, is an app I plan created to stream music to multiple people. Currently, the application stores admins' playback and song information in two seperate tables in a database.
By using the Spotify Web API I authenticate users, retrieve song covers, and retrieve song names. Then using HTMLAudioElement I can create an audio player for users that load the website. Using HTMLMediaElement I can create listeners that trigger
ajax post requests to various PHP files I made containing SQL queries. These PHP files vary minorly in purpose, but the main idea boils down to two concepts updating or selecting data. Using all of the this I effectively created a synced song
position, progress bar, current song name, pause state, and current song cover. All of these are centered around the admins' instance, but I would like to in the future make it more independent allowing non-admins to not be seperate from the admins'
playback. I also would like to further develop features such as printing current time and duration, skip and back buttons, and reseting the current song and position to 0 when the admin(i.e. me) leaves the site.

Check Out the Web App:
https://spotify.crystallizedimagination.com/auth.php

auth.php:

Prepares for the authorization of the use of the Spotify Web API in my application. The app is authorized to use the Spotify Web API through the Client ID and Client Secret
stored in the $session variable upon its initialization. Then it generates a state stored in the session variable storedState. Next the scope, the permissions I will need
users to authorize before they can use my app, is declared. These scopes allow me to retrieve account information, such as ids, and get playlist information. The generated
state and scopes are then sent to be authorized at the authorizeURL stored in $session.

callback.php:

On this page my accounts Client ID and Client Secret are used to make requests to the Spotify Web API. The Client ID, Client Secret, and callback URL are stored in the $session.
state is then retrieved and stored in $state and the storedState session variable is stored in $storedState. These two variables are used to check if the state matches to prevent
users from connected directly to my app before logging in to a spotify account and authorizing the scopes. If the state and storedState match then an access token is requested from
the Spotify Web API. This access token is gotten and stored in $accessToken, next the refresh token is gotten and stored in $refreshToken. Then, $accessToken is stored in the session
variable access and $refreshToken is stored in the session variable refresh. Last, the user is sent to the app's main page app.php.

app.php:

app.php is the main file for my application and where the music streamer/player is located. When users are loaded on the site the first thing it does is store the session variable
access in $accessToken, the session variable refresh in $refreshToken, and it sets the APIAccessToken to $accessToken. After, it retrieves the user's spotify account
information(their uri, id, username, etc.) and stores the user's id in $id. Next the html is started(declaring title, style, and script links) and the main script element is started.
In the main script element lies the functionality of the app. First, the script declares all the global variables(player, playB, pauseB, id, paused, and covers[]) and initializes
covers[] by appending each playlistTrack cover image url to covers[] by retrieving each url from the Spotify Web API using the playlist id to get the tracks. Second, the main function
play() is initialized. At the beginning of play(), the playlist array, position variable, volC, and the i(index) variable are initialized, also the name, pausedA, and tmp variables
are declared. After, it creates the audio player and sets stores the user's id. It then checks whether the user is an admin(kuzoto) if not it does not show the pause button. Then it
displays volume and checks whether it needs to make a POST to updateCurrentTrack.php or getAdminTrack.php and getCurrentTrack.php. Next, it adds the event listeners for the
player(such as play, ended, timeupdate, durationchange, pause, etc.). It also creates the songName label, progress bar, inputs the current songs cover, sets default volume, and begins
playback. if the user isn't an admin user it gets the admins position and seeks the player to that position. The play event sets the paused variable to 0 and updates the admins pause
state if id == "kuzoto". The loadeddata listener stores the current song duration into duration variable. The ended listener checks increments the index, updatesCurrentTrack if the
user is an admin, gets the current song's name, changes the songName, changes the cover, changes the player.src, and plays the new track as long as the end of the playlist hasn't been
reached. The durationchange event updates the duration variable with the new songs duration and changes the max of the progress element. The timeupdate event updates the position
variable, sets the value of progress to player.currentTime, and if the user is an admin it update the stored position. The pause event updates the paused variable and if the user is
an admin user it updates the stored paused state. If the user is not an admin user it also creates an interval to check if the stored paused state has changed. Third, the SetVolume()
function is initialized to change the player volume and volumeLabel everytime the slider input's value changes. Fourth, the pause() function is initialized to pause the player, hide
the pause button, change the play button's onclick function to resume, and show the play button. Fifth, the resume() function is intialized to resume the player, hide the play button,
and show the pause button. Now this script element ends and the here the body of the player is written. The div playlistcontainer contains the entire player and playlist.
img cover contains the cover image for the current track. div songInfo contains the songName and songProgress elements. div slidecontainer contains the volume slider and label.
Then, php retrieves the playlist tracks covers, names, and urls from the Spotify Web API and echos them in html to create a playlist track list. Last, the html ends.

Ip2m360g.php: A secret file shhhhhh

This file is for the webpage where users can input their spotify id, email, and their own password. This input is then inserted into the admins table of my database to create a new admin account.

getAdminTrack.php:

This file is called through an ajax post if the user is not an admin. It retrieves the current track stored for an admin user(Currently only kuzoto).

getCurrentTrack.php:

This file is called by the ended event and towards the beginning of the play function to get the name of the current track using the i(index)+1.

getPauseState.php:

This file is called by an ajax POST in an interval function if the user is not an admin. This selects the admin users paused value, this is then used to check if the admin user's paused state differs
from the current users paused state.

getPosition.php:

This is called by an ajax POST in the play function if the user is not an admin. This file retrieves the admin's last stored position value and echos it back to the ajax POST.

updateCurrentTrack.php:

This is called by ajax POSTs toward the beginning of the play function and inside the ended event listener if the user is an admin. It stores the admin's current track index in their current_track column.

updatePauseState.php:

This is called by ajax POSTs passing the paused variable in the pause and play events if the user is an admin. It stores the admin's current paused state in their paused column.

updatePosition.php:

This is called by an ajax POST in the timeupdate event if the user is an admin. It receives player.currentTime and updates the admin's position column with player.currentTime's value.

songs:
is a file containing all the mp3s for the songs in the playlist.







