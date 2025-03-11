<?php
if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $temp = isset($_GET["temp"]) ? floatval($_GET["temp"]) : 0;
    $humidity = isset($_GET["humidity"]) ? floatval($_GET["humidity"]) : 0;
    $soil = isset($_GET["soil"]) ? intval($_GET["soil"]) : 0;
    $motion = isset($_GET["motion"]) ? intval($_GET["motion"]) : 0;

    // Save to file (or use a database)
    $data = json_encode(["temp" => $temp, "humidity" => $humidity, "soil" => $soil, "motion" => $motion]);
    file_put_contents("sensor_data.json", $data);

    // Send response
    echo json_encode(["status" => "success", "message" => "Data received"]);
} else {
    echo json_encode(["status" => "error", "message" => "Invalid request"]);
}
?>
