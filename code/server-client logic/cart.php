<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
<script src="JQuery/jquery-3.4.1dev.js" > </script>

<body>

  <h2>Scanned Goods</h2>

  <div id="items"></div>

<script type="text/javascript">
  function display()
  {
    xmlhttp=new XMLHttpRequest();
    xmlhttp.open("GET","select.php",false);
    xmlhttp.send(null);
    document.getElementById('items').innerHTML=xmlhttp.responseText;

  }

display();

setInterval(
  function(){display();},2000
);

</script>
</head>




</body>
</html>