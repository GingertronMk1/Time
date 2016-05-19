<?php
include 'db.php';   //Includes the database connection

$newCDName = $_GET["newalbum"];

$getCDID = "SELECT artID FROM CD WHERE(cdName='" . $newCDName . "');";
if($result = $conn->query($getCDID)) {
  $newCDIDArr = $result->fetch_row();
  $newCDID = urlencode($newCDIDArr[0]);
} else {
  echo "Couldn't find album";
}

$newTrackName = urlencode($_GET["newname"]);
$newTrackLength = urlencode($_GET["newlength"]);
$trackID = urlencode($_GET["id"]);


$sql = "UPDATE Track SET cdID=". $newCDID . ", trackTitle='" . $newTrackName . "', trackLength=" . $newTrackLength . " WHERE(trackID=" . $trackID . ");";
$stmt = $conn->prepare($sql);
$stmt->bind_param('isd', $newartID, $newTrackName, $newTrackLength);
$result = $stmt->execute();
if($result) {
  header("Location: ../trackspage.php?albumID=0");
} else {
  echo "Error adding album: " . mysqli_error($conn) . " " . $newArtName . " " . $newartID . " " . $newTrackName . " " . $newTrackLength . " " . $newCDGenre . " " . $newCDTrackNo ;
  printf("<br><a href='../trackspage'>Click here to return to list of tracks</a>");
}

mysqli_close($conn);
?>
