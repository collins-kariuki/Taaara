//RFID module
#include <SPI.h>
#include <MFRC522.h>

//keypad
#include <Keypad.h>

//WiFi
#include "WiFiEsp.h"


  /////////////////////////////////////////////////////////
 //       RFID   declaration                            //
/////////////////////////////////////////////////////////
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String scanedProd_Uid;

  /////////////////////////////////////////////////////////
 //       keypad declaration                            //
/////////////////////////////////////////////////////////
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = {40, 41, 42, 43}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 45, 46, 47}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  // Create keypad instance

//wifi connection.
char ssid[] = "E5830-cbfa";            // your network SSID (name)
char pass[] = "30833861";           // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//server connection
char server[] = "192.168.1.100";

// Initialize the wifi client object
WiFiEspClient client;

//setup section.
void setup() {
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


   // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  
  printWifiStatus();
}

void loop() {

  char key = keypad.waitForKey();
  if (key == 'A') {
      Serial.println(F("Scan PICC to see UID..."));

      // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
      }
      
      scanedProd_Uid = mfrc522.Picc_returnUid(&(mfrc522.uid));

      Serial.println(scanedProd_Uid.length());
//--------------------------------------------------------------------------------//
  // if there's incoming data from the net connection send it out the serial port
  // this is for debugging purposes only
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
    httpRequest();

  };    
}



void httpRequest()
{
  Serial.println();
    
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
    client.println("Host: 192.168.1.100");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
  }
}


void printWifiStatus()
{
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