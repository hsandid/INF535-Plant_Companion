<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

// Include data base connect class
$filepath = realpath(dirname(__FILE__));
require_once($filepath . "/db_connect.php");


//Creating Array for JSON response
$response = array();

if (isset($_POST['plant_id'])) {
    $plant_id = testinputsercurity($_POST['plant_id']);
    $sql = "SELECT status FROM config WHERE plant_id = '$plant_id'";
    $rslt = mysqli_query($conn, $sql);
    if ($rslt->num_rows == 1) {
        if ($rslt->fetch_assoc()['status'] == 1) {
            $temperature = testinputsercurity($_POST['temperature']);
            $humidity = testinputsercurity($_POST['humidity']);
            $light = testinputsercurity($_POST['light']);
            $color = testinputsercurity($_POST['color']);
            $moisture = testinputsercurity($_POST['moisture']);
            


            $result = mysqli_query($conn, "INSERT INTO sensor_data(plant_id,moisture, humidity, light, color, temperature) VALUES('$plant_id','$moisture', '$humidity', '$light', '$color', '$temperature')");

            if ($result) {
                $response["success"] = 1;
                $response["message"] = "Sensor Data updated successfully";

                echo json_encode($response);
            }
            else {
                $response["success"] = 0;
                $response["message"] = "Something went wrong";

                echo json_encode($response);
            }

        }
        else {
            $response["success"] = 0;
            $response["message"] = "Device not activated";

            echo json_encode($response);
        }    }
    else {
        $response["success"] = 0;
        $response["message"] = "Device not configured";

        echo json_encode($response);    }
}else {
    $response["success"] = 0;
    $response["message"] = "Missing field plant_id";

    echo json_encode($response);    }
?>