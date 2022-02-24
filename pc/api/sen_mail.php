<?php
$to = ""; // Send email to our user
$vsubject = "";
$message = "";

$headers = 'From: ' . $myemail . ' ' . "\r\n";
$headers .= "MIME-Version: 1.0" . "\r\n";
$headers .= "Content-type:text/html;charset=UTF-8" . "\r\b";
$u = mail($to, $vsubject, $message, $headers);

?>