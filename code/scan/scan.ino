//WiFi
#include "WiFiEsp.h"

//RFID module
#include <SPI.h>
#include <MFRC522.h>

//keypad
#include <Keypad.h>

//lcd
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //lcd(RS, E, D4, D5, D6, D7)pinout

 //RFID   declaration
#define RST_PIN         5       
#define SS_PIN          53         

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String scanedProd_Uid;
String number;//PhoneNumber


 //keypad declaration
const byte ROWS = 4;
const byte COLS = 4; 
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = {40, 41, 42, 43};
byte colPins[COLS] = {44, 45, 46, 47}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  // keypad instance

//wifi connection.
char ssid[] = "col";            
char pass[] = "collins...";           
int status = WL_IDLE_STATUS;   

//server connection
char server[] = "192.168.43.177";

// Initialize the wifi client object
WiFiEspClient client;

/////setup section.//////

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(3,0);
  lcd.print("Welcome To");
  lcd.setCursor(4,1);
  lcd.print(" Taara ");
  delay(5000);
  


  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial1);


 //RFID
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  // Serial.println(F("Scan PICC to see UID..."));

   // check for the presence of the esp wifi shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
}

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    lcd.clear();
    lcd.print("Attempting to connect to WPA SSID: ");
    lcd.setCursor(0,1);
    lcd.println(ssid);
    
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  lcd.clear();
  lcd.print("You're connected");
  printWifiStatus();



}

void loop() {
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Press A to shop");

  Serial.println("Press A to start shopping");

  char key = keypad.waitForKey();
  while(key == 'A'){

    lcd.clear();
    lcd.print("Scan a Product");
    Serial.println("Scan a Product");
    scanGoods();
    
  };




  /*	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
  scanedProd_Uid = mfrc522.Picc_returnUid(&(mfrc522.uid));

  Serial.println(scanedProd_Uid.length());
	// Dump debug info about the card; PICC_HaltA() is automatically called
	//mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
      // Serial.println(F("Scan PICC to see UID..."));
      // scanGood();

  //--------------------------------------------------------------------------------//
  // if there's incoming data from the net connection send it out the serial port
  // this is for debugging purposes only
  while (client.available()) {
    char c = client.read();
    //Serial.println(c);
    Serial.write(c);

  }
    delay(1000);
    httpRequest();*/
}


void httpRequest(){

  Serial.println();

  String dump;//stores response from the server
    
  // close any connection before send a new request
  // this will free the socket on the WiFi shield
  client.stop();
  String b = "4567891230";
  // if there's a successful connection
  if (client.connect(server, 80)) {
    Serial.println("Connecting...");
    
    // send the HTTP PUT request
    client.print("GET /arduino.php?uid=");
    client.print(scanedProd_Uid);
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.43.177");
    client.println("Connection: close");
    client.println();

    Serial.println("sent...");

   //record incoming bytes

    while (client.available()) {
      char c = client.read();
      Serial.write(c);
      dump+=c;
    }

    Serial.println("Dump coming");

    Serial.println(dump.length());
    Serial.println(dump);
    lcd.clear();

    // send response to customer
    if(dump.length()==248){
      lcd.clear();
      lcd.println("Product Added..");
      delay(2000);
      lcd.clear();
      lcd.print("Scan a Product");

    }else if(dump.length()==347){
      lcd.clear();
      lcd.println("Already Scanned.");
      delay(2000);
      lcd.clear();
      lcd.print("Scan a Product"); 

    }else {
      lcd.clear();
      lcd.println("Error 1.....");
      delay(2000);
      lcd.clear();
      lcd.print("Scan a Product");          
    }

  }
  else {
    // if you couldn't make a connection
    lcd.clear();
    lcd.print("Connection failed");
    Serial.println("Connection failed");
  }
}


void printWifiStatus(){
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

int scanGood(){
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
  
  scanedProd_Uid = mfrc522.Picc_returnUid(&(mfrc522.uid));
  Serial.println(scanedProd_Uid.length());

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Scanned");

  delay(1000);
  httpRequest();
  
}


void scanGoods(){
  while(scanGood() == 0){
    char key1 = keypad.getKey();
    //b pressed call payment function
    if(key1 == 'B'){
      lcd.clear();
      lcd.print("M-pesa");
      delay(1000);
      mpesa();
      
    }else
    {
      scanGood();
    }

  }

}

void mpesa(){
  number = getphonenumber();
  httpRequest_mpesa();


}

String getphonenumber(){
  String PhoneNumber="";

  lcd.clear();
  lcd.print("Enter M-Pesa number");
  
  for(int i=0; i<12; i++){
    char key2 = keypad.waitForKey();
    PhoneNumber += key2;
    lcd.setCursor(i,1);
    lcd.print(key2);
  }
  // Serial.println(PhoneNumber);
  lcd.clear();
  lcd.print("You entered");
  lcd.setCursor(0,1);
  lcd.print(PhoneNumber);
  delay(2000);
  lcd.clear();
  lcd.print("Press C to confirm any other key to repeat");//need to scroll text

  char key3 = keypad.waitForKey();
  if(key3 == 'C'){
    lcd.clear();
    lcd.print("Confirmed");
    return PhoneNumber;
  }else
  {
    getphonenumber();
  
  }
    
 
}


void httpRequest_mpesa()
{
  lcd.clear();
  lcd.print("Processing...");
  String dump2;//stores response from the server
  //char server[] = "http://97766fd3.ngrok.io";
  // close any connection before send a new request
  client.stop();

  // if there's a successful connection
  if (client.connect(server, 80)) {
    Serial.println("Connecting...");
    
    // send the HTTP PUT request
    client.print("GET /mpesa.php?number=");
    client.print(number);
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.43.177");
    client.println("Connection: close");
    client.println();
    
   //record incoming bytes

    while (client.available()) {
      char c = client.read();
      Serial.write(c);
      dump2+=c;
    }

    Serial.println("Dump coming");

    Serial.println(dump2.length());
    Serial.println(dump2);


    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Thank You for");
    lcd.setCursor(0,1);
    lcd.print("shopping with us");
    delay(2000);
    // setup();
  }


  else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
    lcd.clear();
    lcd.print("Trans Failed");

  }
}