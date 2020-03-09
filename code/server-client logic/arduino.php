<?php

$var1 = $_GET['uid'];
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "cart";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$sql = "INSERT INTO incoming (u_id, d_id)
VALUES ($var1, '001')";

//for debugging on browser
if (mysqli_query($conn, $sql)) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}

mysqli_close($conn);

//log file
echo $var1;

file_put_contents('t.txt',$var1,FILE_APPEND);

$var2=file_get_contents('t.txt');

echo $var2;
echo $var2;


?> 