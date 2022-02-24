<?php 
session_start();
include '../security.php';

?>

<h1>Welcome <?php echo $_SESSION["user"]?> to your dashboard</h1>