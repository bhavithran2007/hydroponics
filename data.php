<?php
header('Content-Type: application/json');

if (file_exists("sensor_data.json")) {
    echo file_get_contents("sensor_data.json");
} else {
    echo json_encode(["temp" => 0, "humidity" => 0, "soil" => 0, "motion" => 0]);
}
?>
