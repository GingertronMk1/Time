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
                    <a href="albumspage.php?artID=0">
                        Albums
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div class="mainheader" id="headertracks">
                    <a href="trackspage.php?albumID=0">
                        Tracks
                    </a>
                    <div class="underliner">
                    </div>
                </div>
                <div id="logo">
                  <img id="vinylpic" src="vinyl.png"></img>
                </div>
            </div>
        </div>
        <div class="pagecenter" id="welcomemessage">
            Welcome to the Record Record!<br><br>
            <?php
            include 'BackPHP/db.php';
            $trackCount = return_array($conn, "SELECT COUNT(DISTINCT trackID) FROM Track");
            $cdCount = return_array($conn, "SELECT COUNT(DISTINCT cdID) FROM CD");
            $artCount = return_array($conn, "SELECT COUNT(DISTINCT artID) FROM Artist");
            printf("<p>You currently have %s songs</p>
            <p>By %s artists</p>
            <p>Across %s albums</p>",
            $trackCount[0], $artCount[0], $cdCount[0]);
             ?>
        </div>
    </body>
</html>
