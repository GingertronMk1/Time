<html>
    <head>
        <title>The Record Record</title>
        <link rel="stylesheet" href="../style.css">
        <script src='../validation.js'></script>
    </head>
    <body>
        <div id="main">
            <div id="header">
                <div class="mainheader" id="headerhome">
                    <a href="../index.php">
                        Home
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headerartists">
                    <a href="../artistspage.php">
                        Artists
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headeralbums">
                    <a href="../albumspage.php?artID=0">
                        Albums
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headertracks">
                    <a href="../trackspage.php?albumID=0">
                        Tracks
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div id="logo">
                  <img id="vinylpic" src="../vinyl.png"></img>
                </div>
            </div>
        </div>
        <form action="../BackPHP/updatetrack.php" name="trackform" class="pagecenter" onsubmit="return validateTrackForm()">
          <table class='inputtable'>
            <?php
            include '../BackPHP/db.php';
            $ID = $_GET['id'];
            $trackQuery = "SELECT * FROM Track WHERE(trackID=" . $ID .");";
            $trackInfo = return_array($conn, $trackQuery);
            printf("<tr><td>Album:</td><td><select name='newalbum'>");
            if($result = $conn->query('SELECT * FROM CD')) {
              while($albumName = $result->fetch_row()) {
                if($trackInfo[1] == $albumName[0]) {
                  printf("<option selected value ='%s'>%s</option>", $albumName[2], urldecode($albumName[2]));
                } else {
                printf("<option value ='%s'>%s</option>", $albumName[2], urldecode($albumName[2]));
              }
            }
            };
            printf("</select></td></tr>
            <tr><td>Track Name:</td><td><input type='text' name='newname' value='%s'></td></tr>
            <tr><td>Track Length (s):</td><td><input type='text' name='newlength' value='%s'></td></tr>
            <tr><input type='text' name='id' class='idinput' value=%s></tr>",
            urldecode($trackInfo[2]), $trackInfo[3], $ID);
            //printf("<br>TrackID: %s<br>cdID: %s<br>TrackName: %s<br>TrackLength: %s<br>", $trackInfo[0], $trackInfo[1], $trackInfo[2], $trackInfo[3]);
            ?>
          </table>
            <input type='Submit' value='Update'>
            <?php
            //printf("<a class='fakebutton' href='../BackPHP/deleteartist.php?id=%s'>Delete</a>", $_GET["id"]);
            $deleteURL = "../BackPHP/deletetrack.php?id=" . $_GET["id"];
            printf("<a class='deletebutton' href=%s><input type='button'value='Delete'/></a>", $deleteURL);
            ?>
        </form>
    </body>
</html>
