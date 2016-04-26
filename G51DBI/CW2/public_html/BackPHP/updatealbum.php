<?php
include 'db.php';   //Includes the database connection

$artID = $_GET["id"];
$newArtName = urlencode($_GET["newname"]);

$sql = "UPDATE Artist SET artName='" . $newArtName . "' WHERE artID=" . $artID . ";";

if (mysqli_query($conn, $sql)) {
    header("Location: ../albumspage.php");
} else {
    echo "Error updating record: " . mysqli_error($conn);
}
mysqli_close($conn);
?>
