<?php
include 'db.php';   //Includes the database connection

$idToDel = $_GET["id"];

$artSQL = "DELETE FROM Artist WHERE(artID=" . $idToDel . ");";
$cdSQL = "DELETE FROM CD WHERE(artID=" . $idToDel . ")";

$cdIDs = return_array($conn, "SELECT cdID FROM CD WHERE(CD.artID = " . $idToDel . ")");

for($i = 0; $i < count($cdIDs); $i++){
  $trackSQL = "DELETE FROM Track WHERE(cdID=" . $cdIDs[$i] . ")";
  if(!mysqli_query($conn, $trackSQL)){
      echo "Error updating record: " . mysqli_error($conn);
      printf("<br><a href='../Updating/artist.php?id=%s'>Click here to return to the previous page</a>", $idToDel);
    }
};

if (mysqli_query($conn, $cdSQL)) {
  if(mysqli_query($conn, $artSQL)){
    header("Location: ../artistspage.php");
  } else {echo "Error updating record: " . mysqli_error($conn);
  printf("<br><a href='../Updating/artist.php?id=%s'>Click here to return to the previous page</a>", $idToDel);
}
} else {
    echo "Error updating record: " . mysqli_error($conn);
    printf("<br><a href='../Updating/artist.php?id=%s'>Click here to return to the previous page</a>", $idToDel);
};
mysqli_close($conn);
?>
