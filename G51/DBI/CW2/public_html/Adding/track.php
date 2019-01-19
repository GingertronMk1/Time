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
        <form action="../BackPHP/newtrack.php" name="trackform" class="pagecenter" onsubmit="return validateTrackForm()">
          <table class='inputtable'>
            <?php
            include '../BackPHP/db.php';
            $albumID = $_GET["albumID"];
            $artistNameQuery = 'SELECT cdName FROM CD';
            printf("<tr><td>Album:</td><td><select name='newalbum'>");
            if($result = $conn->query('SELECT * FROM CD')) {
              while($albumName = $result->fetch_row()) {
                if($albumID == $albumName[0]) {
                  printf("<option selected value ='%s'>%s</option>", $albumName[2], urldecode($albumName[2]));
                } else {
                printf("<option value ='%s'>%s</option>", $albumName[2], urldecode($albumName[2]));
              }
            }
            };
            printf("</select></td></tr>
            <tr><td>Track Name:</td><td><input type='text' name='newname'></td></tr>
            <tr><td>Track Length (s):</td><td><input type='text' name='newlength'></td></tr>");
            ?>
          </table>
            <input type='Submit' value='Add'>
        </form>
    </body>
</html>
