<?php
include "db.php";
$res = $conn->query("SELECT * FROM readings ORDER BY id DESC LIMIT 20");
echo "<table border=1><tr><th>ID</th><th>Value</th><th>Time</th></tr>";
while($row = $res->fetch_assoc()){
  echo "<tr><td>".$row["id"]."</td><td>".$row["value"]."</td><td>".$row["created_at"]."</td></tr>";
}
echo "</table>";
?>
