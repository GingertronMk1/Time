<?php
include 'db.php';   //Includes the database connection

$newArtName = $_GET["newname"];

$sql = "INSERT INTO Artist (artName) VALUES ('" . $newArtName . "');";

if (mysqli_query($conn, $sql)) {
    header("Location: ../artistspage.php");
} else {
    echo "Error updating record: " . mysqli_error($conn);
}
mysqli_close($conn);
?>
