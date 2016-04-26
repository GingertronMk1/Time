<?php
include 'db.php';   //Includes the database connection

$newArtName = $_GET["newartist"];

$getartID = "SELECT artID FROM Artist WHERE(artName='" . $newArtName . "');";
if($result = $conn->query($getartID)) {
  $newartIDArr = $result->fetch_row();
  $newartID = $newartIDArr[0];
} else {
  echo "Couldn't find artist";
}

$newCDName = urlencode($_GET["newname"]);
$newCDPrice = $_GET["newprice"];
$newCDGenre = $_GET["newgenre"];
$newCDTrackNo = $_GET["newtrackno"];

$cdID = $_GET["id"];

$sql = "UPDATE CD(artID,cdName,cdPrice,cdGenre,cdTracks) VALUES (?,?,?,?,?) WHERE(cdID=" . $cdID . ");";
$stmt = $conn->prepare($sql);
$stmt->bind_param('sssss', $newartID, $newCDName, $newCDPrice, $newCDGenre, $newCDTrackNo);
$result = $stmt->execute();
if($result) {
  header("Location: ../albumspage.php");
} else {
  echo "Error adding album: " . mysqli_error($conn) . " " . $newArtName . " " . $newartID . " " . $newCDName . " " . $newCDPrice . " " . $newCDGenre . " " . $newCDTrackNo ;
  printf("<br><a href='../albumspage'>Click here to return to list of albums</a>");
}

mysqli_close($conn);
?>
