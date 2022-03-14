<?php
include 'header.php';

$target_dir = "uploads/";


// Check if image file is a actual image or fake image
if (isset($_POST["rate"])) {
    $milliseconds = round(microtime(true) * 1000);
    $target_file = $target_dir .$milliseconds. "-". basename($_FILES["plantImage"]["name"]);

    $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
    $error = array();
    $rating  = $_POST["rating"];
    $check = getimagesize($_FILES["plantImage"]["tmp_name"]);

    $plant_id = $_SESSION["plant_id"];

// Check file size
if ($_FILES["plantImage"]["size"] > 500000) {
    array_push($error, "Sorry, your file is too large.");
}

// Allow certain file formats
if ($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
&& $imageFileType != "gif") {
    array_push($error, "Sorry, only JPG, JPEG, PNG & GIF files are allowed.");
}

// Check if $uploadOk is set to 0 by an error
if(!empty($error)){
    foreach ($error as $value) {
  ?>
    <div class="alert  alert-solid alert-warning" role="alert" style="padding:2%">
    <i style='color:red';><?php echo $value?> </i> 
                                       
    </div>

    <?php
    }
    ?>
        <a href="index.php"  class="btn btn-primary btn-block">Click here to return</a>
<?php
  }
else {
    if (move_uploaded_file($_FILES["plantImage"]["tmp_name"], $target_file)) {
        $result = mysqli_query($conn, "INSERT INTO rating(image_url,rating, plant_id) VALUES('$target_file','$rating', '$plant_id')");

        if ($result) {
            echo "<script>alert('Your rating has been submitted, click OK to return to dashboard');window.location.href ='index.php'</script>";
        }
        else {
            echo "<script>alert('Error, please try again');window.location.href ='index.php'</script>";

        }


    }
    else {
        echo "Sorry, there was an error uploading your file.";
    }
}
}
?>