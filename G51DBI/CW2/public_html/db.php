<?php
//Provide more information if something's wrong with the code
error_reporting(-1);
ini_set('display_errors', 'On');

//Settings to connect to the db
$db_host = 'mysql.nott.ac.uk';
$db_user = 'psyje5';
$db_pass = 'Putitiny0urbutthole';
$db_name = 'psyje5';

$conn = new mysqli($db_host, $db_user, $db_pass, $db_name);
if($conn->connect_errno) echo "Failed to connect to database";
?>
