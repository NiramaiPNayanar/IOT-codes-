<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sensor Readings</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 40px 20px;
        }
        
        .container {
            max-width: 900px;
            margin: 0 auto;
            background: white;
            border-radius: 12px;
            box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);
            overflow: hidden;
        }
        
        .header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 30px;
            text-align: center;
        }
        
        .header h1 {
            font-size: 28px;
            font-weight: 600;
            margin-bottom: 8px;
        }
        
        .header p {
            opacity: 0.9;
            font-size: 14px;
        }
        
        .table-wrapper {
            overflow-x: auto;
        }
        
        table {
            width: 100%;
            border-collapse: collapse;
        }
        
        th {
            background: #f8f9fa;
            color: #495057;
            font-weight: 600;
            text-transform: uppercase;
            font-size: 12px;
            letter-spacing: 0.5px;
            padding: 16px 20px;
            text-align: left;
            border-bottom: 2px solid #dee2e6;
        }
        
        td {
            padding: 16px 20px;
            color: #495057;
            font-size: 14px;
            border-bottom: 1px solid #e9ecef;
        }
        
        tr:last-child td {
            border-bottom: none;
        }
        
        tbody tr {
            transition: background-color 0.2s ease;
        }
        
        tbody tr:hover {
            background-color: #f8f9fa;
        }
        
        .id-cell {
            color: #667eea;
            font-weight: 600;
        }
        
        .value-cell {
            font-weight: 500;
            color: #28a745;
        }
        
        .time-cell {
            color: #6c757d;
            font-size: 13px;
        }
        
        @media (max-width: 600px) {
            th, td {
                padding: 12px 15px;
                font-size: 13px;
            }
            
            .header h1 {
                font-size: 24px;
            }
        }
    </style>
    <script>
        // Auto refresh every 5 seconds
        setTimeout(function(){
            location.reload();
        }, 5000);
    </script>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>📊 Sensor Readings</h1>
            <p>Latest 20 readings</p>
        </div>
        <div class="table-wrapper">
            <?php
            include "db.php";
            $res = $conn->query("SELECT * FROM readings ORDER BY id DESC LIMIT 20");
            echo "<table><thead><tr><th>ID</th><th>Value</th><th>Time</th></tr></thead><tbody>";
            while($row = $res->fetch_assoc()){
                echo "<tr><td class='id-cell'>".$row["id"]."</td><td class='value-cell'>".$row["value"]."</td><td class='time-cell'>".$row["created_at"]."</td></tr>";
            }
            echo "</tbody></table>";
            ?>
        </div>
    </div>
</body>
</html>
