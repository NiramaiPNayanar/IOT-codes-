<?php include "db.php"; ?>
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>ESP32 Sensor Dashboard</title>
<style>
    body {
        margin: 0;
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        background: linear-gradient(135deg, #0a0a0f, #1c1c1c);
        color: #e0e0e0;
        display: flex;
        flex-direction: column;
        align-items: center;
        min-height: 100vh;
    }

    h2 {
        margin-top: 30px;
        font-size: 26px;
        color: #00b4d8;
        
    }

    #data-table {
        width: 85%;
        margin: 30px auto;
        border-collapse: collapse;
        background: rgba(25, 25, 25, 0.85);
        border: 1px solid #2a2a2a;
        box-shadow: 0 0 15px rgba(0, 180, 216, 0.3);
        border-radius: 10px;
        overflow: hidden;
    }

    #data-table th, #data-table td {
        padding: 12px;
        text-align: center;
        border-bottom: 1px solid #333;
    }

    #data-table th {
        background: #111;
        color: #00b4d8;
        text-transform: uppercase;
        letter-spacing: 1px;
    }

    #data-table tr:nth-child(even) {
        background: #181818;
    }

    #data-table tr:hover {
        background: #252525;
    }

    #alert {
        color: #ff4d4d;
        font-weight: bold;
        font-size: 1.1rem;
        margin-top: 15px;
            }

    #cooler {
        margin-top: 8px;
        font-weight: bold;
        font-size: 1rem;
    }

    .cooler-on {
        color: #00ff99;
    }

    .cooler-off {
        color: #888;
    }

    button {
        background: #00b4d8;
        color: #fff;
        border: none;
        border-radius: 6px;
        padding: 12px 18px;
        font-size: 1rem;
        cursor: pointer;
        margin: 20px;
        transition: all 0.2s ease-in-out;
        
    }

    button:hover {
        background: #0077b6;
        box-shadow: 0 0 15px #00b4d8;
    }

    footer {
        margin-top: auto;
        font-size: 0.85rem;
        color: #777;
        padding: 15px;
    }
</style>
</head>
<body>
    <h2>ESP32 Temperature & Slot Sensor Dashboard</h2>
    
    <div id="sensor-data">
        <table id="data-table">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Temperature (°C)</th>
                    <th>Slot Status</th>
                    <th>Status</th>
                    <th>Timestamp</th>
                </tr>
            </thead>
            <tbody id="data-body">
                <tr><td colspan="5">Loading...</td></tr>
            </tbody>
        </table>

        <p id="alert"></p>
        <p id="cooler" class="cooler-off">Cooler OFF</p>
    </div>

    <button onclick="manualRefresh()">Refresh Data</button>


<script>
    function loadData() {
        fetch("fetch_data.php")
        .then(res => res.json())
        .then(data => {
            const tbody = document.getElementById("data-body");
            tbody.innerHTML = "";

            if (data.length > 0) {
                const latest = data[0];
                const temp = parseFloat(latest.temperature);
                const slot = latest.slot_status;
                const status = latest.status;

                data.forEach(row => {
                    tbody.innerHTML += `
                        <tr>
                            <td>${row.id}</td>
                            <td>${row.temperature}</td>
                            <td>${row.slot_status}</td>
                            <td>${row.status}</td>
                            <td>${row.created_at}</td>
                        </tr>`;
                });

                const alertBox = document.getElementById("alert");
                const coolerBox = document.getElementById("cooler");

                if (status === "ABNORMAL") {
                    alertBox.textContent = "               ABNORMAL STATUS DETECTED!";
                } else {
                    alertBox.textContent = "";
                }

                if (status === "ABNORMAL") {
                    coolerBox.textContent = "Abnormal! Cooler OFF";
                    coolerBox.className = "cooler-off";
                } else if (slot === "ON") {
                    coolerBox.textContent = "Cooler ON (Slot Active)";
                    coolerBox.className = "cooler-on";
                } else {
                    coolerBox.textContent = "Cooler OFF";
                    coolerBox.className = "cooler-off";
                }
            } else {
                tbody.innerHTML = "<tr><td colspan='5'>No data found</td></tr>";
            }
        })
        .catch(err => console.error("Error loading data:", err));
    }

    function manualRefresh() {
        loadData();
    }

    window.onload = function() {
        loadData();
        setInterval(loadData, 5000);
    };
</script>
</body>
</html>
