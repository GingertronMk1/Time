<?php
include 'db.php';   //Includes the database connection

$messageSender = $_GET['sender'];
$messageText = $_GET['message'];

$sql = "INSERT_INTO message (messageSender, messageText) VALUES (?, ?)";
$stmt = $conn->prepare($sql);
$stmt->bind_param('ss', $messageSender, $messageText);
$result = $stmt->execute();
if (!$result) echo "Failed to insert record";
?>
