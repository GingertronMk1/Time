<?php
include 'db.php';   //Includes the database connection

$newArtName = $_GET["newartist"];

$getartID = "SELECT artID FROM Artist WHERE(artName='" . $newArtName . "');";
if($result = $conn->query($getartID)) {
  $newartIDArr = $result->fetch_row();
  $newartID = urlencode($newartIDArr[0]);
} else {
  echo "Couldn't find artist";
}

$newCDName = urlencode($_GET["newname"]);
$newCDPrice = urlencode($_GET["newprice"]);
$newCDGenre = urlencode($_GET["newgenre"]);
$newCDTrackNo = urlencode($_GET["newtrackno"]);
$cdID = $_GET["id"];

$sql = "UPDATE CD SET artID= " . $newartID . ", cdName='" . $newCDName . "', cdPrice=" . $newCDPrice . ", cdGenre='" . $newCDGenre . "', cdTracks=" . $newCDTrackNo . " WHERE(cdID=" . $cdID . ");";
$stmt = $conn->prepare($sql);
$stmt->bind_param('isdsi', $newartID, $newCDName, $newCDPrice, $newCDGenre, $newCDTrackNo);
$result = $stmt->execute();
if($result) {
  header("Location: ../albumspage.php?artID=0");
} else {
  echo "Error adding album: " . mysqli_error($conn) . " " . $newArtName . " " . $newartID . " " . $newCDName . " " . $newCDPrice . " " . $newCDGenre . " " . $newCDTrackNo ;
  printf("<br><a href='../albumspage'>Click here to return to list of albums</a>");
}

mysqli_close($conn);
?>
