<?php

include 'header.php';

$plant_id = $_SESSION["plant_id"];

$latest_data = "SELECT * FROM rating WHERE plant_id='$plant_id' ORDER BY id DESC LIMIT 25";
$latest_data = mysqli_query($conn, $latest_data);
if (mysqli_num_rows($latest_data) > 0) {
?>

<div class="container" style="padding: 10%">
<h2>Your Plant Ratings</h2>
<table class="table table-hover">
  <thead>
    <tr>
      <th>Rating ID</th>
      <th>Plant ID</th>
      <th>Rating</th>
      <th>Image</th>
    </tr>
  </thead>
  <tbody>
      <?php while ($row = $latest_data->fetch_assoc()) {
    echo "<tr><td>" . $row["id"] . "</td><td>" . $row["plant_id"] . "</td><td>" . $row["rating"] . "</td><td><a href='" . $row["image_url"] . "' target='_blank'><img src='" . $row["image_url"] . "' class='img-fluid' style='max-width: 75px; max-height: 75px'/></a></td></tr>";
  }
?>
  </tbody>
</table>
</div>

<?php
}
else {
?>




    <?php
}

include 'footer.php';

?>