<html>
    <head>
        <title>The Record Record</title>
        <link rel="stylesheet" href="../style.css">
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
                    <a href="../albumspage.php">
                        Albums
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headertracks">
                    <a href="../trackspage.php">
                        Tracks
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div id="logo">
                </div>
            </div>
        </div>
        <form action="../BackPHP/newalbum.php" class="pagecenter">
          <table class='inputtable'>
            <?php
            include '../BackPHP/db.php';
            $artistNameQuery = 'SELECT artName FROM Artist';
            printf("<tr><td>Album Artist:</td><td><select name='newartist'>");
            if($result = $conn->query($artistNameQuery)) {
              while($artistName = $result->fetch_row()) {
                $artistNameDecoded = urldecode($artistName[0]);
                printf("<option value = '%s'>%s</option>", $artistName[0], $artistNameDecoded);
              };
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
