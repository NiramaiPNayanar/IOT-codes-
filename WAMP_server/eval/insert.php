<?php
include "db.php";
if (isset($_GET["value"])) {
  $val = intval($_GET["value"]);
  $conn->query("INSERT INTO readings (value) VALUES ($val)");
  echo "OK";
} else {
  echo "NO";
}
?>
