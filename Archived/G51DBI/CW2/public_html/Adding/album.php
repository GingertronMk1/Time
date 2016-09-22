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
        <form action="../BackPHP/newalbum.php" name="albumform" class="pagecenter" onsubmit="return validateAlbumForm()">
          <table class='inputtable'>
            <?php
            include '../BackPHP/db.php';
            $artID = $_GET["artID"];
            $artistNameQuery = 'SELECT artName FROM Artist';
            printf("<tr><td>Album Artist:</td><td><select name='newartist'>");
            if($result = $conn->query('SELECT * FROM Artist')) {
              while($artistName = $result->fetch_row()) {
                if($artID == $artistName[0]) {
                  printf("<option selected value ='%s'>%s</option>", $artistName[1], urldecode($artistName[1]));
                } else {
                printf("<option value ='%s'>%s</option>", $artistName[1], urldecode($artistName[1]));
              }
            }
            };
            printf("</select></td></tr>
            <tr><td>Album Name:</td><td><input type='text' name='newname'></td></tr>
            <tr><td>Album Price:</td><td><input type='text' name='newprice'></td></tr>
            <tr><td>Album Genre:</td><td><input type='text' name='newgenre'></td></tr>
            <tr><td>Number of Tracks:</td><td><input type='text' name='newtrackno'></td></tr>");
            ?>
          </table>
            <input type='Submit' value='Add'>
        </form>
    </body>
</html>
