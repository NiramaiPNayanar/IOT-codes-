<?php
include "db.php";
$res = $conn->query("SELECT * FROM readings ORDER BY id DESC LIMIT 20");
?>
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="refresh" content="2">
  <style>
    body {
      margin: 0;
      font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
      background: linear-gradient(135deg, #e0f7fa, #f1f8e9);
      color: #333;
      display: flex;
      flex-direction: column;
      align-items: center;
    }

    h1 {
      margin: 30px 0 20px;
      font-size: 28px;
      color: #007BFF;
      text-align: center;
    }

    table {
      border-collapse: collapse;
      width: 70%;
      max-width: 900px;
      background: #fff;
      border-radius: 12px;
      overflow: hidden;
      box-shadow: 0 4px 20px rgba(0,0,0,0.1);
    }

    th, td {
      padding: 14px 18px;
      text-align: center;
    }

    th {
      background: #007BFF;
      color: #fff;
      font-size: 16px;
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }

    tr:nth-child(even) {
      background: #f8f9fa;
    }

    tr:hover {
      background: #e3f2fd;
      transition: 0.3s;
    }

    td {
      font-size: 15px;
    }
  </style>
</head>
<body>
  <h1>WAMP Server- Lab Evaluation</h1>
  <table>
    <tr><th>ID</th><th>Value</th><th>Time</th></tr>
    <?php
    while($row = $res->fetch_assoc()){
      echo "<tr><td>".$row["id"]."</td><td>".$row["value"]."</td><td>".$row["created_at"]."</td></tr>";
    }
    ?>
  </table>
</body>
</html>
