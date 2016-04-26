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
        <form action="../BackPHP/updatealbum.php" class="pagecenter">
          <table class='inputtable'>
            <?php
            include '../BackPHP/db.php';
            $albumID = $_GET['id'];
            printf("<tr><td>Album Artist:</td><td><select name='newartist'>");
            if($result = $conn->query('SELECT artName FROM Artist ORDER BY artID ASC')) {
              while($artistName = $result->fetch_row()) {
                $artistNameDecoded = urldecode($artistName[0]);
                printf("<option value = '%s'>%s</option>", $artistName[0], $artistNameDecoded);
              };
            };
            $cdQuery = "SELECT * FROM CD WHERE(cdID=" . $albumID .");";
            $albumInfo = return_array($conn, $cdQuery);
            printf("</select></td></tr>
            <tr><td>Album Name:</td><td><input type='text' name='newname' value='%s'></td></tr>
            <tr><td>Album Price:</td><td><input type='text' name='newprice' value='%s'></td></tr>
            <tr><td>Album Genre:</td><td><input type='text' name='newgenre' value='%s'></td></tr>
            <tr><td>Number of Tracks:</td><td><input type='text' name='newtrackno' value='%s'></td></tr>
            <tr><input type='text' name='id' class='idinput' value=%s></tr>",
            urldecode($albumInfo[2]), $albumInfo[3], $albumInfo[4], $albumInfo[5], $albumID);
            ?>
          </table>
            <input type='Submit' value='Update'>
        </form>
    </body>
</html>
