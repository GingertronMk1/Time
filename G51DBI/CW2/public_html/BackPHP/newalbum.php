<?php
include 'db.php';   //Includes the database connection

$newArtName = $_GET["newartist"];
$newCDName = $_GET["newname"];
$newCDPrice = $_GET["newprice"];
$newCDGenre = $_GET["newgenre"];
$newCDTrackNo = $_GET["newtrackno"];

$sql = "INSERT INTO CD (cdName, cdPrice, cdGenre, cdTracks) VALUES ('" . $newCDName . "," . $newCDPrice . "," . $newCDGenre "," $newCDTrackNo"');";

if (mysqli_query($conn, $sql)) {
    header("Location: ../albumspage.php");
} else {
    echo "Error updating record: " . mysqli_error($conn);
}
mysqli_close($conn);
?>
