<?php
if (isset($_GET['motor'])) {
    file_put_contents("motor_state.txt", $_GET['motor']);
    echo "Motor set to " . $_GET['motor'];
}
if (isset($_GET['pir'])) {
    file_put_contents("pir_state.txt", $_GET['pir']);
    echo "PIR set to " . $_GET['pir'];
}
?>
