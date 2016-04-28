<?php
include 'db.php';   //Includes the database connection

$idToDel = $_GET["id"];

$sql = "DELETE FROM CD WHERE(cdID=" . $idToDel . ");";

if (mysqli_query($conn, $sql)) {
    header("Location: ../albumspage.php?artID=0");
} else {
    echo "Error updating record: " . mysqli_error($conn);
    printf("<br><a href='../Updating/album.php?id=%s'>Click here to return to the previous page</a>", $idToDel);
}
mysqli_close($conn);
?>
