<?php

include 'header.php';

$checkid = "SELECT * FROM config WHERE user='$user'";
$plant_id_check = mysqli_query($conn, $checkid);
$no_of_plants = mysqli_num_rows($plant_id_check);
if ($no_of_plants > 0) {
  $pid = "SELECT plant_id FROM config WHERE user='$user'";
  $pid = mysqli_query($conn, $pid);
  $plant_id = $pid->fetch_assoc()['plant_id'];
  $_SESSION["plant_id"] = $plant_id;
  $latest_data = "SELECT * FROM sensor_data WHERE plant_id='$plant_id' ORDER BY update_time DESC LIMIT 25";
  $latest_data = mysqli_query($conn, $latest_data);
  if(mysqli_num_rows($latest_data) > 0){
  $data = $latest_data->fetch_assoc();
  $moisture = $data['moisture'];
  $humidity = $data['humidity'];
  $light = $data['light'];
  $color = $data['color'];
  $last_update = $data['update_time'];
  $temperature = $data['temperature'];

?>


    <div class="home-content">

    <form method="POST" action="rate.php" enctype="multipart/form-data">
    <div class="modal fade" id="modalLoginForm" tabindex="-1" role="dialog" aria-labelledby="myModalLabel"
  aria-hidden="true">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header text-center">
        <h4 class="modal-title w-100 font-weight-bold">Hello, help us rate your plant health </h4>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body mx-3">
        <div class="d-flex flex-row align-items-center mb-4">
                    <i class="fas fa-envelope fa-lg me-3 fa-fw"></i>
                    <div class="form-outline flex-fill mb-0">
                    <div class="form-group">
                    <input type="file" id="imageFile" name="plantImage" class="form-control validate" required>
                    </div>
                      <label class="form-label" for="form3Example3c">Select Plant Picture</label>
                    </div>
                  </div>

        <div class="d-flex flex-row align-items-center mb-4">
                    <i class="fas fa-envelope fa-lg me-3 fa-fw"></i>
                    <div class="form-outline flex-fill mb-0">
                    <div class="form-group">
                      <select class="form-control" id="rating" name="rating">
                        <option value="Healthy">Healthy</option>
                        <option value="Not Healthy">Not Healthy</option>
                      </select>
                    </div>
                      <label class="form-label" for="form3Example3c">Select Your Plant Health</label>
                    </div>
                  </div>

      </div>
      <div class="modal-footer d-flex justify-content-center">
        <button class="btn btn-secondary" type="submit" name="rate" >Submit Rating</button>
      </div>
    </div>
  </div>
</div>
  </form>


<div class="text-center">
  <a href="" class="btn btn-success btn-rounded mb-4" data-toggle="modal" data-target="#modalLoginForm">Rate Your Plant <i class='bx bxs-tree cart two'></i></a>
</div>



    <div class="overview-boxes">
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Soil Moisture</div>
            <div class="number"><?php echo $moisture ?> %</div>
            <!-- <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div> -->
          </div>
          <i class='bx bx-cloud-drizzle cart' ></i>
          <!-- <i class='bx cloud-drizzle'></i> -->
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Humidity</div>
            <div class="number"><?php echo $humidity ?>%</div>
            <!-- <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div> -->
          </div>
          <i class='bx bxs-cloud cart two' ></i>
          <!-- <i class='bx bxs-cart-add cart two' ></i> -->
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Temperature</div>
            <div class="number"><?php echo $temperature ?>°C</div>
            <!-- <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div> -->
          </div>
          <i class='bx bxs-droplet cart three'></i>
          <!-- <i class='bx bx-cart cart three' ></i> -->
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Leaf Color</div>
            <div class="number"><?php echo $color ?></div>
            <!-- <div class="indicator">
              <i class='bx bx-down-arrow-alt down'></i>
              <span class="text">Down From Today</span>
            </div> -->
          </div>
          <i class='bx bxs-tree cart two'></i>
          <!-- <i class='bx bxs-cart-download cart four' ></i> -->
        </div>
      </div>
      <div class="overview-boxes">
        <!-- <div class="box">
          <div class="right-side">
            <div class="box-topic">Light Intensity</div>
            <div class="number"></div>
          </div>
          <i class='bx bx-sun cart 2'></i>
        </div> -->
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Last Update</div>
            <div class="numbder"><?php echo $last_update ?></div>
            <!-- <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div> -->
          </div>
          <i class='bx bxs-time-five cart two'></i>
          <!-- <i class='bx bxs-cart-add cart two' ></i> -->
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Plant ID</div>
            <div class="numbr"><?php echo $plant_id ?></div>
            <!-- <div class="indicator">
              <i class='bx bx-up-arrow-alt'></i>
              <span class="text">Up from yesterday</span>
            </div> -->
          </div>
          
          <i class='bx bxs-devices cart three bx-rotate-90' ></i>
          <!-- <i class='bx bx-cart cart three' ></i> -->
        </div>
        <div class="box">
          <div class="right-side">
            <div class="box-topic">Active Plants</div>
            <div class="number"><?php echo $no_of_plants ?></div>
            <!-- <div class="indicator">
              <i class='bx bx-down-arrow-alt down'></i>
              <span class="text">Down From Today</span>
            </div> -->
          </div>
          <i class='bx bx-wifi cart'></i>
          <!-- <i class='bx bxs-cart-download cart four' ></i> -->
        </div>
      </div>
      <div class="container-fluid" id="irrigateField">
          <button type="button" id="irrigateBtn" class="btn btn-success btn-block btn-lg btn-round">Irrigate Plant</button>
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
        <th>Leaf Color</th>
      </tr>
    </thead>
    <tbody>
        <?php
        while($row = $latest_data->fetch_assoc()) {
          echo "<tr><td>".$row["update_time"]."</td><td>".$row["moisture"]."</td><td>".$row["temperature"]."</td><td>".$row["humidity"]."</td><td>".$row["color"]."</td></tr>";
        }
        ?>
    </tbody>
  </table>
</div>
    </div>
  </section>


  <?php
}else {

  ?>

<div class="container" style="padding:20%">

<div class="alert alert-warning">
    <strong>Ooops!</strong> You have available data from your companion.
  </div>

</div>

<?php
}}else {

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



<script>
$('#irrigateField').on('click', function () {
  irrigateDevice(1);
});

// $(document).onload(function () {
//   checkDeviceStatus(irrigate);
// });

$(window).on('load', function () {
  checkDeviceStatus(1);
});

function irrigateDevice(data) {
  $.ajax({
    url: "irrigate.php",
    cache: false,
    type: "POST",
    data: { irrigate: data },
    success: function (html) {
      $("#irrigateField").html(html);
    }
  });
}

function checkDeviceStatus(data) {
  $.ajax({
    url: "irrigate.php",
    cache: false,
    type: "POST",
    data: { checkDevice: data },
    success: function (html) {
      $("#irrigateField").html(html);
    }
  });
}
</script>