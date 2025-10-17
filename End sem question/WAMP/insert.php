<?php
include "db.php";

if (isset($_GET["temperature"]) && isset($_GET["slot"])) {
    $temperature = floatval($_GET["temperature"]);
    $slot        = $_GET["slot"] === "ON" ? "ON" : "OFF";
    $status      = ($temperature > 31) ? "ABNORMAL" : "NORMAL";

    $sql = "INSERT INTO sensor_data (temperature, slot_status, status) 
            VALUES ($temperature, '$slot', '$status')";
    if ($conn->query($sql) === TRUE) {
        echo "OK";
    } else {
        echo "DB Error: " . $conn->error;
    }
} else {
    echo "Invalid Data";
}

$conn->close();
?>
