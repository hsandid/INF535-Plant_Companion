<?php 
include 'header.php';


$error = array();


if (isset($_POST["plant"])) {
  #code
  $pid=testinputsercurity($_POST["device_id"]);
  $checkid = "SELECT * FROM config WHERE plant_id='$pid'";
  $plant_id_check = mysqli_query($conn, $checkid);



  #checks

  if (empty($pid)) {
    # code...
    array_push($error,"Plant ID required");
    
    }  elseif (mysqli_num_rows($plant_id_check) <= 0) {
        # code...
        array_push($error,"Invalid plant ID");
      }elseif($plant_id_check->fetch_assoc()['user'] != null){
        array_push($error,"Plant ID already registered");
      }else if(empty($error)){

      $q="UPDATE config SET status=1, user='$user' WHERE plant_id='$pid'";
     $dbc= mysqli_query($conn,$q);
     if($dbc){
        echo "<script>alert('You have added a new companion device');window.location.href ='index.php'</script>";
     }else{
        echo "<script>alert('Server error, try again');</script>";
     }
     
    }
}
     ?>

   <section class="vh-100" style="background-color: #eee;">
  <div class="container h-100">
    <div class="row d-flex justify-content-center align-items-center h-100">
      <div class="col-lg-12 col-xl-11">
        <div class="card text-black" style="border-radius: 25px;">
          <div class="card-body p-md-5">
            <div class="row justify-content-center">
              <div class="col-md-10 col-lg-6 col-xl-5 order-2 order-lg-1">

                <p class="text-center h1 fw-bold mb-5 mx-1 mx-md-4 mt-4">Add new companion device</p>

                <?php if(!empty($error)){
                    foreach ($error as $value) {
                  ?>
                    <div class="alert  alert-solid alert-warning" role="alert">
                    <i style='color:red';><?php echo $value?> </i>                                     
                    </div>
                    <?php
                    }
                  }
                  ?>

                <form class="mx-1 mx-md-4" method="POST" action="">

                  <div class="d-flex flex-row align-items-center mb-4">
                    <i class="fas fa-envelope fa-lg me-3 fa-fw"></i>
                    <div class="form-outline flex-fill mb-0">
                      <input type="text" id="form3Example3c" name="device_id" class="form-control" />
                      <label class="form-label" for="form3Example3c">Your Device ID</label>
                    </div>
                  </div>

                  <div class="d-flex justify-content-center mx-4 mb-3 mb-lg-4">
                    <button type="submit" name="plant" class="btn btn-primary btn-block">Add Companion Device</button>
                
                  </div>
                

                </form>

              </div>

            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</section>

    <?php 
include 'footer.php';

?>