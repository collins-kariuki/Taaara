<!DOCTYPE html>
<html>
<head>
<style>
table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  width: 100%;
}

td, th {
  border: 1px solid #cccccc;
  text-align: left;
  padding: 8px;
}

tr:nth-child(even) {
  background-color: #dddddd;
}
</style>
</head>
<body>

<h2>Scanned Goods</h2>

<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "store";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$sql = "SELECT barcode,p_name,price FROM cart ";
$result = $conn->query($sql);
    echo "<table>
  <tr>
    <th>Item</th>
    <th>Description</th>
    <th>Price</th>
  </tr>";
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>" . $row["barcode"]. "</td><td>" . $row["p_name"]. "</td><td> " . $row["price"]. "</td></tr>";
    }
    echo "</table>";
//  else {
    // echo "0 results";
// }


?>





</body>
</html>