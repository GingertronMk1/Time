<?php
include 'db.php';   //Includes the database connection

$idToDel = $_GET["id"];

$sql = "DELETE FROM Track WHERE(trackID=" . $idToDel . ");";

if (mysqli_query($conn, $sql)) {
    header("Location: ../trackspage.php?albumID=0");
} else {
    echo "Error updating record: " . mysqli_error($conn);
    printf("<br><a href='../Updating/track.php?id=%s'>Click here to return to the previous page</a>", $idToDel);
}
mysqli_close($conn);
?>
