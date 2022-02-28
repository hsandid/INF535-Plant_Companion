<?php

include 'header.php';

$checkid = "SELECT * FROM config WHERE user='$user'";
$plant_id_check = mysqli_query($conn, $checkid);
$no_of_plants = mysqli_num_rows($plant_id_check);
if ($no_of_plants > 0) {
  $pid = "SELECT plant_id FROM config WHERE user='$user'";
  $pid = mysqli_query($conn, $pid);
  $plant_id = $pid->fetch_assoc()['plant_id'];
  $latest_data = "SELECT * FROM sensor_data WHERE plant_id='$plant_id' ORDER BY update_time DESC LIMIT 25";
  $latest_data = mysqli_query($conn, $latest_data);
  $data = $latest_data->fetch_assoc();
  $moisture = $data['moisture'];
  $humidity = $data['humidity'];
  $light = $data['light'];
  $color = $data['color'];
  $last_update = $data['update_time'];
  $temperature = $data['temperature'];

?>
    <div class="home-content">
    <div class="overview-boxes">
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Soil Moisture</div>
            <div class="number"><?php echo $moisture ?> %</div>
            <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div>
          </div>
          <i class='bx bx-cart-alt cart'></i>
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Humidity</div>
            <div class="number"><?php echo $humidity ?></div>
            <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div>
          </div>
          <i class='bx bxs-cart-add cart two' ></i>
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Temperature</div>
            <div class="number"><?php echo $temperature ?>°C</div>
            <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div>
          </div>
          <i class='bx bx-cart cart three' ></i>
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Light Reflected</div>
            <div class="number"><?php echo $color ?></div>
            <div class="indicator">
              <i class='bx bx-down-arrow-alt down'></i>
              <span class="text">Down From Today</span>
            </div>
          </div>
          <i class='bx bxs-cart-download cart four' ></i>
        </div>
      </div>
      <div class="overview-boxes">
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Light Intensity</div>
            <div class="number"><?php echo $light ?></div>
            <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div>
          </div>
          <i class='bx bx-cart-alt cart'></i>
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Last Update</div>
            <div class="numbder"><?php echo $last_update ?></div>
            <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div>
          </div>
          <i class='bx bxs-cart-add cart two' ></i>
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Plant ID</div>
            <div class="number"><?php echo $plant_id ?></div>
            <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div>
          </div>
          <i class='bx bx-cart cart three' ></i>
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Number of Active Plants</div>
            <div class="number"><?php echo $no_of_plants ?></div>
            <div class="indicator">
              <i class='bx bx-down-arrow-alt down'></i>
              <span class="text">Down From Today</span>
            </div>
          </div>
          <i class='bx bxs-cart-download cart four' ></i>
        </div>
      </div>

      <div class="container">
  <h2>Sensor Update Log</h2>
  <table class="table table-hover">
    <thead>
      <tr>
        <th>Updated</th>
        <th>Moisture</th>
        <th>Tempertaure</th>
        <th>Humidity</th>
        <th>Color</th>
        <th>Light</th>
      </tr>
    </thead>
    <tbody>
        <?php
        while($row = $latest_data->fetch_assoc()) {
          echo "<tr><td>".$row["update_time"]."</td><td>".$row["moisture"]."</td><td>".$row["temperature"]."</td><td>".$row["humidity"]."</td><td>".$row["color"]."</td><td>".$row["light"]."</td></tr>";
        }
        ?>
    </tbody>
  </table>
</div>
    </div>
  </section>


  <?php
}
else {

?>

<div class="container" style="padding:20%">

<div class="alert alert-warning">
    <strong>Ooops!</strong> You have no registered companion devicle <a href="plant.php" class="alert-link">click here to add your device</a>.
  </div>

</div>

<?php
}

include 'footer.php';

?>