<?php
include "connection.php";

$dev_id = $_GET['dev_id'];
$session_id = $_GET['session_id'];

//get the json callback
$postData = file_get_contents('php://input');
//ecode to an assosiative array
$callback_decoded = json_decode($postData,true);

$ResultCode = $callback_decoded["Body"]["stkCallback"]["ResultCode"];
$Receipt_no = $callback_decoded["Body"]["stkCallback"]["CallbackMetadata"]["Item"][1]["Value"];
$PhoneNumber = $callback_decoded["Body"]["stkCallback"]["CallbackMetadata"]["Item"][3]["Value"];
$Amount = $callback_decoded["Body"]["stkCallback"]["CallbackMetadata"]["Item"][0]["Value"];

$sql = "INSERT INTO `transactions`(trans_id, dev_id, phone_no, session_id, amount)
        VALUES('$Receipt_no', '$dev_id', '$PhoneNumber', '$session_id', '$Amount')";
echo ($ResultCode);
echo ($Receipt_no);
echo ($PhoneNumber);
echo ($Amount);

if($ResultCode == 0){
    mysqli_query($conn,$sql);
    
}


$file = fopen("logi.txt", "w"); //url fopen should be allowed for this to occur
if(fwrite($file, $postData) === FALSE)
{
    fwrite("Error: no data written");
}

fwrite("\r\n");
fclose($file);

// echo '{"ResultCode": 0, "ResultDesc": "The service was accepted successfully", "ThirdPartyTransID": "1234567890"}';


?>
<?php
include "connection.php";
$sql = "SELECT `p_name`,`price` FROM `cart`";
$data = mysqli_query($conn,$sql);

if (! $data){
    echo(failed);
}
$sms = "\n--------  Product and Price\n";
while($row = mysqli_fetch_assoc($data)){
 
        $sms = "$sms{$row['p_name']} @ Ksh. {$row['price']} \r\n" ;
}

echo($sms);


require __DIR__ . '/vendor/autoload.php';
use Twilio\Rest\Client;

$account_sid = 'AC17fa4cbfda79b74fec3ba7e47d006241';
$auth_token = 'e02b422e465a783bd7d65b80acb68302';

$twilio_number = "+19283795393";

$client = new Client($account_sid, $auth_token);
$client->messages->create(
    // Where to send a text message (your cell phone?)
    '+254795390809',
    array(
        'from' => $twilio_number,
        'body' => $sms
    )
);