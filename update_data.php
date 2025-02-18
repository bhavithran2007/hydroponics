<?php
if (isset($_GET['temp']) && isset($_GET['humidity']) && isset($_GET['soil']) && isset($_GET['motion'])) {
    $data = $_GET['temp'] . "," . $_GET['humidity'] . "," . $_GET['soil'] . "," . $_GET['motion'];
    file_put_contents("sensor_data.txt", $data);
    echo "Data updated";
}
?>
