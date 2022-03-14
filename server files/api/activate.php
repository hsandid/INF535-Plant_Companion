<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

// Include data base connect class
$filepath = realpath(dirname(__FILE__));
require_once($filepath . "/db_connect.php");


//Creating Array for JSON response
$response = array();

if (isset($_GET['plant_id'])) {
    $plant_id = testinputsercurity($_GET['plant_id']);
    $sql = "SELECT * FROM config WHERE plant_id = '$plant_id'";
    $rslt = mysqli_query($conn, $sql);
    if ($rslt->num_rows == 1) {
        $row = $rslt->fetch_assoc();

        $status = $row['status'];
        $ssid = $row['ssid'];
        $password = $row['password'];
        $moisture_threshold = $row['moisture'];
        $manual_pump = $row['manual_pump'];

        $response["success"] = 1;
        $response["status"] = $status;
        $response["ssid"] = $ssid;
        $response["password"] = $password;
        $response["moisture_threshold"] = $moisture_threshold;
        $response["manual_pump"] = $manual_pump;

        echo json_encode($response);
    }
}
?>