<?php
include 'db.php';   //Includes the database connection

$newCDName = $_GET["newalbum"];

$getCDID = "SELECT cdID FROM CD WHERE(cdName='" . $newCDName . "');";
if($result = $conn->query($getCDID)) {
  $newCDIDArr = $result->fetch_row();
  $newCDID = $newCDIDArr[0];
} else {
  echo "Couldn't find album";
}

$newTrackName = urlencode($_GET["newname"]);
$newTrackLength = $_GET["newlength"];

$sql = "INSERT INTO Track(cdID,trackTitle,trackLength) VALUES (?,?,?)";
$stmt = $conn->prepare($sql);
$stmt->bind_param('isi', $newCDID, $newTrackName, $newTrackLength);
$result = $stmt->execute();
if($result) {
  header("Location: ../trackspage.php?albumID=0");
} else {
  echo "Error adding track: " . mysqli_error($conn) . " " . $newCDName . " " . $newCDID . " " . $newTrackName . " " . $newTrackLength;
  printf("<br><a href='../albumspage'>Click here to return to list of tracks</a>");
}

mysqli_close($conn);
?>
