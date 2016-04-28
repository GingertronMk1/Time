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
        <form action="../BackPHP/updateartist.php" name="artistform" class="pagecenter" name="updateartist" onsubmit="return validateArtistForm()">
          Artist Name:
          <?php
          include '../BackPHP/db.php';
          $artistInfo = return_array($conn, "SELECT * FROM Artist WHERE(artID = " . $_GET["id"] . ");");
          $artistName = urldecode($artistInfo[1]);
          printf("<input type='text' name='newname' value='%s'>
          <br><br>
          <input type='text' name='id' class='idinput' value=%s>", $artistName, $_GET["id"]);
          ?>
          <br>
          <input type="submit" text="Update">
          <?php
          //printf("<a class='fakebutton' href='../BackPHP/deleteartist.php?id=%s'>Delete</a>", $_GET["id"]);
          $deleteURL = "../BackPHP/deleteartist.php?id=" . $_GET["id"];
          printf("<a class='deletebutton'  href=%s><input type='button'value='Delete'/></a>", $deleteURL);
          ?>
          <br>
          <br>
          <p class="deletewarning">WARNING: THIS WILL DELETE ALL ALBUMS AND TRACKS ASSOCIATED WITH THIS ARTIST</p>
        </form>
    </body>
</html>
