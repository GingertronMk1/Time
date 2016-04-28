<?php
//Provide more information if something's wrong with the code
error_reporting(-1);
//mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
ini_set('display_errors', 'On');

//Settings to connect to the db
$db_host = 'mysql.cs.nott.ac.uk';
$db_user = 'psyje5';
$db_pass = 'Putitiny0urbutthole1';
$db_name = 'psyje5';

$conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
if($conn->connect_errno) echo "Failed to connect to database";

function return_array($connection, $query) {
  if($result = $connection->query($query)) {
    return $result->fetch_row();
  } else {
    printf("Something's gone wonky<br>");
  }
}
?>
