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
          <form action="/Searches/artistspage.php">
            <input type="search" name="q" placeholder="Search Artists by Name..."></input>
            <input type="Submit" value="Search">
          </form>
				<?php
						include 'BackPHP/db.php';
						$query = 'SELECT * FROM Artist ORDER BY `artID`';
						if ($result = $conn->query($query)) {
							printf("<table><tr><th>ID</th><th>Name</th><th class='actioncol'>Actions</th></tr>");
							$fields = $result->fetch_fields();
							$x = 0;
							while($artist = $result->fetch_row()) {
								$x++;
								$class = ($x%2 == 0)? 'greybackground': 'whitebackground';
								echo "<tr class='$class'>";
								$artID = $artist[0];
								$artName = urldecode($artist[1]);
								$artURL = "'Updating/artist.php?id=" . $artID . "'";
                $cdURL = "albumspage.php?artID=" . $artID;
								printf("<td>%s</td><td>%s</td><td class='actioncol'><a href=%s>Edit</a> | <a href=%s>Albums</a></td>", $artID, $artName, $artURL, $cdURL);
							}
							printf("</table>");
						}
				 ?>
         <br>
				 <a href="Adding/artist.php"><button>Add a new Artist</button></a>
			 </div>
    </body>
</html>
