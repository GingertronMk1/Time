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
						$query = 'SELECT * FROM Artist ORDER BY `artID`';
						if ($result = $conn->query($query)) {
							printf("<table border='0'>");
							printf("<tr>");
							$fields = $result->fetch_fields();
							printf("<th>ID</th><th>Name</th><th>Actions</th></tr>");
							$x = 0;
							while($artist = $result->fetch_row()) {
								$x++;
								$class = ($x%2 == 0)? 'whiteBackground': 'graybackground';
								echo "<tr class='$class'>";
								$artID = $artist[0];
								$artName = urldecode($artist[1]);
								$artURL = "'Updating/artist.php?id=" . $artID . "&name=" . urlencode($artName) . "'";
								printf("<td>%s</td><td>%s</td><td><a href=%s'>Edit</a></td>", $artID, $artName, $artURL);
							}
							printf("</table>");
						}
				 ?>
         <br>
				 <a href="Adding/artist.php">Add a new Artist</a>
			 </div>
    </body>
</html>
