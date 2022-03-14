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
    $sql = "SELECT status, moisture, user, plant_type FROM config WHERE plant_id = '$plant_id'";
    $rslt = mysqli_query($conn, $sql);

    $moisture_threshold;
    $user;
    if ($rslt->num_rows == 1) {
        $row = $rslt->fetch_assoc();
        $moisture_threshold = $row['moisture'];
        $plantType = $row['plant_type'];
        $user = $row['user'];
        if ($row['status'] == 1) {
            $temperature = testinputsercurity($_POST['temperature']);
            $humidity = testinputsercurity($_POST['humidity']);
            $light = testinputsercurity($_POST['light']);
            $color = testinputsercurity($_POST['color']);
            $moisture = testinputsercurity($_POST['moisture']);



            $result = mysqli_query($conn, "INSERT INTO sensor_data(plant_id,moisture, humidity, light, color, temperature) VALUES('$plant_id','$moisture', '$humidity', '$light', '$color', '$temperature')");

            if ($result) {
                $response["success"] = 1;
                $response["message"] = "Sensor Data updated successfully";

                $t = time();
                $result = mysqli_query($conn, "UPDATE config SET last_update='$t', manual_pump='$light' WHERE plant_id='$plant_id'");

                $brfilterresult = ("SELECT * FROM threshold WHERE plant_type='" . $plantType . "'");

                $result = $conn->query($brfilterresult);
                if ($result->num_rows > 0) {
                    $row = $result->fetch_assoc();
                    $temperature_threshold = $row['temperature'];
                    $humidity_threshold = $row['humidity'];

                }

                if ($moisture < $moisture_threshold || $temperature < $temperature_threshold || $humidity < $humidity_threshold) {

                    $to = $user; // Send email to our user
                    $vsubject = "Notification from Plant Companion";
                    if ($moisture < $moisture_threshold) {
                        $message = "<h2>Your plant moisture level (" . $moisture . "%) is low. Confirm that you still have water in your reservior</h2>";

                    }
                    if ($temperature < $temperature_threshold) {
                        $message .= "<h2>Your plant temperature level (" . $temperature . "°C) is either too low/high.</h2>";

                    }
                    if ($humidity < $humidity_threshold) {
                        $message .= "<h2>Your plant humidity level (" . $humidity . "%) is either too low/high.</h2>";

                    }
                }
                $myemail = "Your Plant Companion";

                $headers = 'From: ' . $myemail . ' ' . "\r\n";
                $headers .= "MIME-Version: 1.0" . "\r\n";
                $headers .= "Content-type:text/html;charset=UTF-8" . "\r\b";
                $u = mail($to, $vsubject, $message, $headers);


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
        }
    }
    else {
        $response["success"] = 0;
        $response["message"] = "Device not configured";

        echo json_encode($response);
    }
}
else {
    $response["Error"] = 0;
    $response["message"] = "Missing field plant_id";

    echo json_encode($response);
}
?>