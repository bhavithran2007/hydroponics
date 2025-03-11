<?php
if ($_SERVER["REQUEST_METHOD"] == "GET") {
    if (isset($_GET["motor"])) {
        $motorState = intval($_GET["motor"]);
        file_put_contents("motor_state.txt", $motorState);
        echo json_encode(["status" => "success", "motor" => $motorState]);
    } elseif (isset($_GET["pir"])) {
        $pirState = intval($_GET["pir"]);
        file_put_contents("pir_state.txt", $pirState);
        echo json_encode(["status" => "success", "pir" => $pirState]);
    } else {
        echo json_encode(["status" => "error", "message" => "Invalid parameter"]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Invalid request"]);
}
?>
