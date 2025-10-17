<?php
$host = "localhost";
$user = "root";
$pass = "";
$db   = "fin_data";

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("DB Connection failed: " . $conn->connect_error);
}
?>
