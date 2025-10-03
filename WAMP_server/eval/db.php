<?php
$host = "localhost";
$user = "root";
$pass = "";
$db   = "ir_data";
$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) { die("DB fail"); }
?>
