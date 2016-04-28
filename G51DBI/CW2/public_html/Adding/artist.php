<html>
    <head>
        <title>The Record Record</title>
        <link rel="stylesheet" href="../../style.css">
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
        <form action="../BackPHP/newartist.php" name="artistform" class="pagecenter" onsubmit="return validateArtistForm()">
          <b>ADD NEW ARTIST</b><br><br>
          New Artist Name:
          <input type='text' name='newname'>
          <br><br>
          <input type="submit" text="Add">
        </form>
    </body>
</html>
