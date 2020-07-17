<?php
include "connection.php";
$number = $_GET['number'];
$dev_id = '1234567890';
$session_id = '100000007';
$sql = "SELECT SUM(price) FROM cart";


  $url = 'https://sandbox.safaricom.co.ke/mpesa/stkpush/v1/processrequest';
  $curl = curl_init();
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type:application/json','Authorization:Bearer auth')); //setting custom header
//amount
$result = mysqli_query($conn,$sql);
$resultarr = mysqli_fetch_assoc($result);
$Amount = $resultarr["SUM(price)"];
  
  
$BusinessShortCode = '174379';
$Timestamp = date('YmdHis',time());
$PhoneNumber = $number;
$PartyA = $PhoneNumber;
$PartyB = '174379';
$AccountReference = 'test';
$TransactionDesc = 'test';
$Passkey ='passkey';
$data = $BusinessShortCode.$Passkey.$Timestamp;
$password = base64_encode($data);

//callback url
$CallBackURLraw = 'http://da03b9381f84.ngrok.io/mpesaCallbackParser.php';
$CallBackURL = $CallBackURLraw.'?dev_id='.$dev_id.'&session_id='.$session_id;
//$CallBackURL = 'https://97766fd3.ngrok.io/mpesaCallbackParser.php?dev_id=1234567890&session_id=100000007';
  
  $curl_post_data = array(
    //Fill in the request parameters with valid values
    'BusinessShortCode' => $BusinessShortCode,
    'Password' => $password,
    'Timestamp' => $Timestamp,
    'TransactionType' => 'CustomerPayBillOnline',
    'Amount' => $Amount,
    'PartyA' => $PartyA,
    'PartyB' => $PartyB,
    'PhoneNumber' => $PhoneNumber,
    'CallBackURL' => $CallBackURL,
    'AccountReference' => $AccountReference,
    'TransactionDesc' => $TransactionDesc
  );
  
  $data_string = json_encode($curl_post_data);
  
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($curl, CURLOPT_POST, true);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $data_string);
  
  $curl_response = curl_exec($curl);
  print_r($curl_response);
  
  echo $curl_response;

  ?>
  
