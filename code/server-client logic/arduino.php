<?php
include "connection.php";

$uid = $_GET['uid'];
$dev_id = '1234567890';
$session_id = '100000007';


$sql = "INSERT INTO incoming (rf_key, dev_id, session_id)
VALUES ($uid, $dev_id, $session_id)";

//for debugging on browser
if (mysqli_query($conn, $sql)) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}

mysqli_close($conn);

//log file
// echo $uid;

file_put_contents('t.txt',$uid,FILE_APPEND);

$var2=file_get_contents('t.txt');

// echo $var2;
// echo $var2;


?> 