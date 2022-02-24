<?php 
session_start();
include 'api/db_connect.php';
 include("header.php");


$error = array();


if (isset($_POST["signup"])) {
  #code
  $name=testinputsercurity($_POST["name"]);
  $email=testinputsercurity($_POST["email"]);
  $password=testinputsercurity($_POST["password"]);
  $cpassword=testinputsercurity($_POST["password2"]);



  #checks
  $checkemail = "SELECT * FROM users WHERE email='$email'";
  $usercheck = mysqli_query($conn, $checkemail);

  if (empty($email)) {
    # code...
    array_push($error,"email required");
    
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
      // check if e-mail address is well-formed
      array_push($error,"invaild email");

    } elseif (mysqli_num_rows($usercheck) > 0) {
      # code...
      array_push($error,"email already registered");
    } elseif (empty($name)) {
      # code...
      array_push($error,"username required");
    } elseif (empty($password)) {
      # code...
      array_push($error,"password required");
    } elseif (empty($cpassword)) {
      # code...
      array_push($error,"confirm password required");
    } elseif ($password !== $cpassword) {
      # code...
      array_push($error,"password doesn't match");
    } else if(empty($error)){

      $q="INSERT INTO users (name, email, password)
      VALUES('$name','$email', '$password')";
     $dbc= mysqli_query($conn,$q);
     if($dbc){
        $_SESSION["user"] = $email;
//         echo"<script>
// swal({
//   title: 'Registration Succesful!',
//   text: ' Redirecting to your dashboard',
//   icon: 'success',
//   button: 'OK!'
// });
// </script>";
// header("Location: Dashboard/index.php");
        echo "<script>alert('Logged In Successfully! click ok to proceed to dashboard');window.location.href ='Dashboard/index.php'</script>";
     }else{
        echo "<script>alert('Server error, try again');</script>";
    //     echo"<script>
    // swal({
    //   title: 'Registration Failed!',
    //   text: 'Try again',
    //   icon: 'failed'
    // });
    // </script>";

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

                <p class="text-center h1 fw-bold mb-5 mx-1 mx-md-4 mt-4">Sign up</p>

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
                    <i class="fas fa-user fa-lg me-3 fa-fw"></i>
                    <div class="form-outline flex-fill mb-0">
                      <input type="text" id="form3Example1c" name="name" class="form-control" />
                      <label class="form-label" for="form3Example1c">Your Name</label>
                    </div>
                  </div>

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

                  <div class="d-flex flex-row align-items-center mb-4">
                    <i class="fas fa-key fa-lg me-3 fa-fw"></i>
                    <div class="form-outline flex-fill mb-0">
                      <input type="password" id="form3Example4cd" name="password2" class="form-control" />
                      <label class="form-label" for="form3Example4cd">Repeat your password</label>
                    </div>
                  </div>

                  <div class="d-flex justify-content-center mx-4 mb-3 mb-lg-4">
                    <button type="submit" name="signup" class="btn btn-primary btn-block">Register</button>
                
                  </div>
                </hr>
                    <p>Already a member, <a href="login.php">login here</a></p>

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