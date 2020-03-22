<?php
    include "connection.php";
?>


    <?php

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


    ?>