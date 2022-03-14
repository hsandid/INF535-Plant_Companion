<?php

session_start();
include '../security.php';
include_once('../api/db_connect.php');
$user = $_SESSION['user'];

if (isset($_POST['irrigate'])) {
    $irrigate = $_POST['irrigate'];
    $plant_id = $_SESSION["plant_id"];
    $q = "UPDATE config SET manual_pump='$irrigate' WHERE plant_id='$plant_id'";
    $dbc = mysqli_query($conn, $q);

    if ($dbc) {
        echo '<button type="button" id="irrigateBtn" class="btn btn-info btn-block">Device Pending Irrigation...</button>';
    }


}

if (isset($_POST['checkDevice'])) {
    $plant_id = $_SESSION["plant_id"];
    $q = "SELECT manual_pump from config  WHERE plant_id='$plant_id'";
    $pid = mysqli_query($conn, $q);
    $status = $pid->fetch_assoc()['manual_pump'];
    if ($status == 1) {
        echo '<button type="button" id="irrigateBtn" class="btn btn-info btn-block">Device Pending Irrigation...</button>';
    }
    else {
        echo '<button type="button" id="irrigateBtn" class="btn btn-success btn-block">Irrigate Plant</button>';
    }


}





?>

