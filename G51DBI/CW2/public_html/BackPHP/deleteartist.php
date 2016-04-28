<?php
include 'db.php';   //Includes the database connection

$idToDel = $_GET["id"];

$sql = "DELETE FROM Artist WHERE(artID=" . $idToDel . ");";

if (mysqli_query($conn, $sql)) {
    header("Location: ../artistspage.php");
} else {
    echo "Error updating record: " . mysqli_error($conn);
    printf("<br><a href='../Updating/artist.php?id=%s'>Click here to return to the previous page</a>", $idToDel);
}
mysqli_close($conn);
?>
