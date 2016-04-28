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
              if($artistID = $_GET["artID"]){
                $query = "SELECT * FROM Artist, CD WHERE(Artist.artID = " . $artistID . " && CD.artID = " . $artistID . ")";
              } else {
                $query = 'SELECT * FROM Artist, CD WHERE(Artist.artID = CD.artID)';
              };
  						if ($result = $conn->query($query)) {
  							printf("<table border='0'><col width=130px>");
  							printf("<tr>");
  							printf("<th>ID</th><th>Artist</th><th>Name</th><th>Price</th><th>Genre</th><th>Tracks</th><th class='actioncol'>Actions</th></tr>");
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
                  $cdGenre = urldecode($CD[6]);
                  $cdTracks = $CD[7];
                  $cdURL = "'/Updating/album.php?id=" . $cdID . "'";
                  $tracksURL = "trackspage.php?albumID=" . $cdID;
  								printf("<td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td class='actioncol'><a href=%s'>Edit</a> | <a href=%s>Tracks</a></td>", $cdID, $artName, $cdName, $cdPrice, $cdGenre, $cdTracks, $cdURL, $tracksURL);
  							}
  							printf("</table>
       				 <br><a href='Adding/album.php?artID=" . $artistID . "'>Add a new Album</a>");
  						}
  				 ?>
  			 </div>
    </body>
</html>
