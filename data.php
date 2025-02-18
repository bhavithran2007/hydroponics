<?php
$data = file_get_contents("sensor_data.txt");
list($temp, $humidity, $soil, $motion) = explode(",", $data);

$response = array(
    "temp" => (float)$temp,
    "humidity" => (float)$humidity,
    "soil" => (float)$soil,
    "motion" => (int)$motion
);

header('Content-Type: application/json');
echo json_encode($response);
?>
