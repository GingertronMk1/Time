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
                <div class="mainheader" id="headerCDs">
                    <a href="artistspage.php">
                        Artists
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headeralbums">
                    <a href="albumspage.php">
                        Albums
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headertracks">
                    <a href="trackspage.php">
                        Tracks
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div id="logo">
                </div>
            </div>
        </div>
        <div class="pagecenter">
  				<?php
  						include 'BackPHP/db.php';
  						$query = 'SELECT * FROM Artist, CD WHERE(Artist.artID = CD.artID);';
  						if ($result = $conn->query($query)) {
  							printf("<table border='0'>");
  							printf("<tr>");
  							printf("<th>ID</th><th>Artist</th><th>Name</th><th>Price</th><th>Genre</th><th>Tracks</th><th>Actions</th></tr>");
  							$x = 0;
  							while($CD = $result->fetch_row()) {
  								$x++;
  								$class = ($x%2 == 0)? 'whiteBackground': 'graybackground';
  								echo "<tr class='$class'>";
  								$artID = $CD[0];
  								$artName = urldecode($CD[1]);
                  $cdID = $CD[2];
                  $cdName = urldecode($CD[4]);
                  $cdPrice = $CD[5];
                  $cdGenre = $CD[6];
                  $cdTracks = $CD[7];
                  $cdURL = "'/Updating/album.php?id=" . $cdID . "'";
  								printf("<td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td><a href=%s'>Edit</a></td>", $cdID, $artName, $cdName, $cdPrice, $cdGenre, $cdTracks, $cdURL);
  							}
  							printf("</table>");
  						}
  				 ?>
  				 <br><a href="Adding/album.php">Add a new Album</a>
  			 </div>
    </body>
</html>
