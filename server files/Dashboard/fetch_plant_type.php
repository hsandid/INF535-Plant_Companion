<?php

session_start();
include '../security.php';
include_once('../api/db_connect.php');
$user = $_SESSION['user'];

$plantType = $_POST['plant_type'];
$brfilterresult = ("SELECT * FROM threshold WHERE plant_type='" . $plantType . "'");


$result = $conn->query($brfilterresult);

if ($result->num_rows > 0) {
  $row = $result->fetch_assoc();
  echo '<div class="card bg-primary">
                    <div class="card-body text-center" >
                    <p class="card-text" style="color:white">Plant Type  ' . $plantType . ' Requirements</p>
                      <p class="card-text">Minimum Soil Mositure Level: ' . $row['moisture'] . '%</p>
                      <p class="card-text">Maximum Ambient Temperature: ' . $row['temperature'] . '°</p>
                      <p class="card-text">Minimum Humidity: ' . $row['humidity'] . '%</p>
                      <p class="card-text">Healthy Leaf Color: ' . $row['light'] . '</p>
                    </div>
                  </div>';



}




?>

