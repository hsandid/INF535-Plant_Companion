/*This is a cron Job that runs every five minutes t check the health of the system and send email as may be required */


<?php

session_start();
include_once('db_connect.php');
$threshold = 5;
$myemail = "kingmr2019@gmail.com";


$q = "SELECT plant_id, last_update, user FROM config";
$q = mysqli_query($conn, $q);
if (mysqli_num_rows($q) > 0) {
    while ($row = $q->fetch_assoc()) {
        $user = $row['user'];
        $plant_id = $row['plant_id'];
        $last_update = $row['last_update'];

        $timediff = time() - $last_update;

        $days = intval($timediff / 86400);
        $remain = $timediff % 86400;
        $hours = intval($remain / 3600);
        $remain = $remain % 3600;
        $mins = intval($remain / 60);
        $secs = $remain % 60;

        if ($mins > $threshold) {
            $timestring = $mins . "M " . $secs . "S ";
            if ($hours > 0)
                $timestring = $hours . "H " . $mins . "M ";
            if ($days > 0)
                $timestring = $days . "D " . $hours . "H ";


            $to = $user; // Send email to our user
            $vsubject = "Loss of Communication with plant companion";
            $message = "Your companion device with ID <b>" . $plant_id . "</b> has not received update for about <b> " . $timestring . "</b>. This may be due to battery rundown or loss of internet connection.";
            $myemail = "Plant Companion";

            $headers = 'From: ' . $myemail . ' ' . "\r\n";
            $headers .= "MIME-Version: 1.0" . "\r\n";
            $headers .= "Content-type:text/html;charset=UTF-8" . "\r\b";
            $u = mail($to, $vsubject, $message, $headers);
        }






    }



}


?>