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
        <form action="../BackPHP/updateartist.php" class="pagecenter">
          Artist Name:
          <?php
          printf("<input type='text' name='newname' value='" .  urldecode($_GET["name"]) . "'>") ?>
          <br><br>
          <?php
            printf("<input type='text' name='id' class='idinput' value=%s>", $_GET["id"]);
           ?>
           <br>
          <input type="submit" text="Update">
        </form>
    </body>
</html>
