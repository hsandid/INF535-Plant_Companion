
<?php


function testinputsercurity($data)
{
	$data = trim($data);
	$data = stripcslashes($data);
	$data = htmlspecialchars($data);
	return $data;
}

//params to connect to a database locally
$dbHost = "localhost";
$dbUser = "root";
$dbPass = "";
$dbName = "plant_companion";

//connection to database
$conn = mysqli_connect($dbHost, $dbUser, $dbPass, $dbName);

if (!$conn) {
	die("Database connection failed!");
}

?>