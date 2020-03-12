<?php
//get the json callback
$callback = file_get_contents('callback.json');
//ecode to an assosiative array
$callback_decoded = json_decode($callback,true);

$ResultCode = $callback_decoded["Body"]["stkCallback"]["ResultCode"];
$Receipt_no = $callback_decoded["Body"]["stkCallback"]["CallbackMetadata"]["Item"][1]["Value"];

echo $Receipt_no;
echo $ResultCode;
?>