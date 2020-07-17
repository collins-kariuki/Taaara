<?php
include "connection.php";

for($i = 100000000;$i < 100000099; $i++){
    $sql = "INSERT INTO `sessions`(`session_id`)
            VALUES ($i)";
    mysqli_query($conn,$sql);
}
echo "success";

?>