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
        <form action="../BackPHP/updatealbum.php" name="albumform" class="pagecenter" onsubmit="return validateAlbumForm()">
          <table class='inputtable'>
            <?php
            include '../BackPHP/db.php';
            $ID = $_GET['id'];
            $cdQuery = "SELECT * FROM CD WHERE(cdID=" . $ID .");";
            $albumInfo = return_array($conn, $cdQuery);
            printf("<tr><td>Album Artist:</td><td><select name='newartist'>");
            if($result = $conn->query('SELECT * FROM Artist')) {
              while($artistName = $result->fetch_row()) {
                if($albumInfo[1] == $artistName[0]) {
                  printf("<option selected value ='%s'>%s</option>", $artistName[1], urldecode($artistName[1]));
                } else {
                printf("<option value ='%s'>%s</option>", $artistName[1], urldecode($artistName[1]));
              }
            }
            };
            printf("</select></td></tr>
            <tr><td>Album Name:</td><td><input type='text' name='newname' value='%s'></td></tr>
            <tr><td>Album Price:</td><td><input type='text' name='newprice' value='%s'></td></tr>
            <tr><td>Album Genre:</td><td><input type='text' name='newgenre' value='%s'></td></tr>
            <tr><td>Number of Tracks:</td><td><input type='text' name='newtrackno' value='%s'></td></tr>
            <tr><input type='text' name='id' class='idinput' value=%s></tr>",
            urldecode($albumInfo[2]), $albumInfo[3], urldecode($albumInfo[4]), $albumInfo[5], $ID);
            //printf("cdID: %s<br>artistID: %s<br>cdName: %s<br>Price: %s<br>cdGenre: %s<br>", $albumInfo[0], $albumInfo[1], $albumInfo[2], $albumInfo[3], $albumInfo[4]);
            ?>
          </table>
            <input type='Submit' value='Update'>
            <?php
            $deleteURL = "../BackPHP/deletealbum.php?id=" . $_GET["id"];
            printf("<a class='deletebutton'  href=%s><input type='button'value='Delete'/></a>", $deleteURL);
            ?>
            <br>
            <br>
            <p class="deletewarning">WARNING: THIS WILL DELETE ALL TRACKS ASSOCIATED WITH THIS ALBUM</p>
        </form>
    </body>
</html>
