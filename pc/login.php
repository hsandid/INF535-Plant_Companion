<?php 
session_start();
include 'api/db_connect.php';
 include("header.php");


$error = array();


if (isset($_POST["login"])) {
    $email=mysqli_real_escape_string($conn,testinputsercurity($_POST["email"]));
    $password=mysqli_real_escape_string($conn,testinputsercurity($_POST["password"]));

    if (empty($email)) {
        # code...
        array_push($error,"Email required");
        
        } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
          // check if e-mail address is well-formed
          array_push($error,"Invaild email");
    
        } elseif (empty($password)) {
          # code...
          array_push($error,"Password required");
        }else if(empty($error)){

    $qlogin=$conn->prepare( "SELECT email FROM users WHERE email = ?");
    $qlogin->bind_param("s",$email);
    $qlogin->execute();
    $qlogin->store_result();

    if ($qlogin->num_rows == 1) {
        # code...
        $qlogin->bind_result($username);
        $qlogin->fetch();
        $qlogin->close();

        $passlogin=$conn->prepare( "SELECT email FROM users WHERE password = ? AND email=?");
        $passlogin->bind_param("ss",$password,$email);
        $passlogin->execute();
        $passlogin->store_result();
        if ($passlogin->num_rows == 1) {
            $_SESSION["user"] = $email;
            echo "<script>alert('Logged In Successfully! click ok to proceed to dashboard');window.location.href ='Dashboard/index.php'</script>";


        }else{
            array_push($error,"Invaild email/password");
        }
    }else{
            array_push($error,"Invaild email/password");
        }

}   }
     ?>





<section class="vh-100" style="background-color: #eee;">
  <div class="container h-100">
    <div class="row d-flex justify-content-center align-items-center h-100">
      <div class="col-lg-12 col-xl-11">
        <div class="card text-black" style="border-radius: 25px;">
          <div class="card-body p-md-5">
            <div class="row justify-content-center">
              <div class="col-md-10 col-lg-6 col-xl-5 order-2 order-lg-1">

                <p class="text-center h1 fw-bold mb-5 mx-1 mx-md-4 mt-4">Login</p>

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
                      <input type="email" id="form3Example3c" name="email" class="form-control" />
                      <label class="form-label" for="form3Example3c">Your Email</label>
                    </div>
                  </div>

                  <div class="d-flex flex-row align-items-center mb-4">
                    <i class="fas fa-lock fa-lg me-3 fa-fw"></i>
                    <div class="form-outline flex-fill mb-0">
                      <input type="password" id="form3Example4c" name="password" class="form-control" />
                      <label class="form-label" for="form3Example4c">Password</label>
                    </div>
                  </div>


                  <div class="d-flex justify-content-center mx-4 mb-3 mb-lg-4">
                    <button type="submit" name="login" class="btn btn-primary btn-block">Login</button>
                
                  </div>
                </hr>
                    <p>Not a member, <a href="signup.php">signup here</a></p>

                </form>

              </div>
              <div class="col-md-10 col-lg-6 col-xl-7 d-flex align-items-center order-1 order-lg-2">

                <img src="img/img_1.jpg" class="img-fluid" alt="Sample image">

              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</section>

<?php include("footer.php") ?>