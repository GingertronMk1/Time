<html>
    <head>
        <title>The Record Record</title>
        <link rel="stylesheet" href="style.css">
    </head>
    <body>
        <div id="main">
            <div id="header">
                <div class="mainheader" id="headerhome">
                    <a href="index.php">
                        Home
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headerartists">
                    <a href="artistspage.php">
                        Artists
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headeralbums">
                    <a href="albumspage.php?artID=0">
                        Albums
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headertracks">
                    <a href="trackspage.php?albumID=0">
                        Tracks
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div id="logo">
                  <img id="vinylpic" src="vinyl.png"></img>
                </div>
            </div>
        </div>
        <div class="pagecenter">
  				<?php
  						include 'BackPHP/db.php';
              if($albumID = $_GET["albumID"]) {
                $query = "SELECT * FROM CD, Track WHERE(CD.cdID = " . $albumID . " && Track.cdID = " . $albumID . ");";
              } else {
                $query = 'SELECT * FROM CD, Track WHERE(CD.cdID = Track.cdID);';
              }
  						if ($result = $conn->query($query)) {
  							printf("<table border='0'>");
  							printf("<tr>");
  							printf("<th>ID</th><th>Album</th><th>Name</th><th>Length(s)</th><th>Actions</th></tr>");
  							$x = 0;
  							while($track = $result->fetch_row()) {
  								$x++;
  								$class = ($x%2 == 0)? 'whiteBackground': 'graybackground';
  								echo "<tr class='$class'>";
                  //The track name, the album it's from, how long it is
  								$cdID = $track[0];
                  $artID = $track[1];
                  $cdName = urldecode($track[2]);
                  $trackID = $track[6];
                  $trackName = urldecode($track[8]);
                  $trackLength = $track[9];
                  $trackURL = "'/Updating/track.php?id=" . $trackID . "'";
  								printf("<td>%s</td><td>%s</td><td>%s</td><td>%s</td><td><a href=%s>Edit</a></td>", $trackID, $cdName, $trackName, $trackLength, $trackURL);
  							}
  							printf("</table>
       				 <br><a href='Adding/track.php?albumID=" . $albumID ."'>Add a new Track</a>");
  						}
  				 ?>
  			 </div>
    </body>
</html>
