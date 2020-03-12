<?php
  $url = 'https://sandbox.safaricom.co.ke/mpesa/stkpush/v1/processrequest';
  
  $curl = curl_init();
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type:application/json','Authorization:Bearer ACCESS_TOKEN')); //setting custom header

  
  $BusinessShortCode = '174379';
  $Timestamp = date('YmdHis',time());
  $Amount = '5';
  $PhoneNumber = '254795580723';
  $PartyA = $PhoneNumber;
  $PartyB =  '600000';
  $AccountReference = 'test';
  $TransactionDesc = 'test';

  $Passkey ='bfb279f9aa9bdbcf158e97dd71a467cd2e0c893059b10f78e6b72ada1ed2c919'
  $data = $BusinessShortCode.$Passkey.$Timestamp;
  $password = base64_encode($data);

  $curl_post_data = array(
    //Fill in the request parameters with valid values
    'BusinessShortCode' => $BusinessShortCode,
    'Password' => $password,
    'Timestamp' => $Timestamp,
    'TransactionType' => 'CustomerPayBillOnline',
    'Amount"' => $Amount,
    'PartyA' => $PartyA,
    'PartyB' => $PartyB,
    'PhoneNumber' => $PhoneNumber,
    'CallBackURL' => 'https://ip_address:port/callback',
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
  