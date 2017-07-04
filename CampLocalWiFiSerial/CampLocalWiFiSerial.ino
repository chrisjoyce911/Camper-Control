#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>


//SSID of your network
char ssid[] = "My WiFi";
char ssidAP[] = "My Camper";
char pass[] = "My WiFi Password";

bool wifiap = false ;
IPAddress ip(192,168,0,200);  //Node static IP
IPAddress gateway(192,168,0,138);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

// D0     GPIO 16 
// D1/SCL GPIO 05 - Software Serial RX
// D2/SDA GPIO 04 - Software Serial TX
// D3     GPIO 00 - 
// D4     GPIO 02 - (Built In Led)
// D5     GPIO 14 - 
// D6     GPIO 12 - 
// D7     GPIO 13 - 
// D8     GPIO 15 - 

SoftwareSerial mySerial(5, 4); // RX, TX (

#define BB_TRUE(bp,bb)    bp |= bb
#define BB_FALSE(bp,bb)   bp &= ~(bb)
#define BB_READ(bp,bb)    bool(bp & bb)
#define BB_TOGGLE(bp,bb)  if(BB_READ(bp,bb)){BB_FALSE(bp,bb);} else {BB_TRUE(bp,bb);}

#define BB_NIGHT_LIGHT    1
#define BB_MAIN_LIGHT     2
#define BB_BED_LIGHT      4
#define BB_KITECHEN_LIGHT 8
#define BB_TRAILER_LIGHT  16
#define BB_STORAGE_LIGHT  32
#define BB_USB_POWER      64
#define BB_CPAP_POWER     128

bool StatusChange = 0 ;
byte LightPack = 0;

String HTMLheader ;
String HTMLbody ;
String HTMLfooter ;
String message ;

void WiFiAP(){
  Serial.println();
  Serial.println();
  Serial.print("Configuring access point...");

   WiFi.softAP(ssidAP, "");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("Go to http://192.168.4.1 in a web browser");
}

void WiFiNetwork(){
  Serial.println();
  Serial.println();
  Serial.print("Configuring as network client...");
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to...");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi connected successfully");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.print("IP address of localIP: ");
  Serial.println(WiFi.localIP());
}

void startserver()
{
  server.on("/", getStatus);
  server.on("/NIGHT_LIGHT", NIGHT_LIGHT);
  server.on("/MAIN_LIGHT",MAIN_LIGHT);
  server.on("/BED_LIGHT",BED_LIGHT);
  server.on("/KITECHEN_LIGHT",KITECHEN_LIGHT);
  server.on("/TRAILER_LIGHT",TRAILER_LIGHT);
  server.on("/STORAGE_LIGHT",STORAGE_LIGHT);
  server.on("/USB_POWER",USB_POWER);
  server.on("/CPAP_POWER",CPAP_POWER);
  server.on("/status", getStatus);
  server.on("/setnetwork",toggleNetwork);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void setup()
{
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(10);

  BB_FALSE(LightPack, BB_NIGHT_LIGHT );
  BB_FALSE(LightPack, BB_MAIN_LIGHT);
  BB_FALSE(LightPack, BB_BED_LIGHT);
  BB_FALSE(LightPack, BB_KITECHEN_LIGHT);
  BB_FALSE(LightPack, BB_TRAILER_LIGHT);
  BB_FALSE(LightPack, BB_STORAGE_LIGHT);
  BB_FALSE(LightPack, BB_USB_POWER);
  BB_FALSE(LightPack, BB_CPAP_POWER);

  showStatus();

  mySerial.begin(4800); 
  
  if (wifiap) {
    WiFiAP();
  } else {
    WiFiNetwork();
  }
  
  startserver() ;
  
}

void loop () {
  server.handleClient();

   if(StatusChange){
      Serial.println(F("Sending New Light Settings"));
      mySerial.write(LightPack);
      StatusChange = 0 ;
   } 
    
  if (mySerial.available()) {
    LightPack = mySerial.read() ;
    showStatus();
    Serial.write(mySerial.read());

  }
  
}

void showStatus() {
  Serial.println(F("====================="));
  
  Serial.print(F("NIGHT_LIGHT status: "));
  Serial.println(BB_READ(LightPack, BB_NIGHT_LIGHT)); 

  Serial.print(F("MAIN_LIGHT status: "));
  Serial.println(BB_READ(LightPack, BB_MAIN_LIGHT)); 

  Serial.print(F("BED_LIGHT status: "));
  Serial.println(BB_READ(LightPack, BB_BED_LIGHT)); 

  Serial.print(F("KITECHEN_LIGHT status: "));
  Serial.println(BB_READ(LightPack, BB_KITECHEN_LIGHT)); 

  Serial.print(F("TRAILER_LIGHT status: "));
  Serial.println(BB_READ(LightPack, BB_TRAILER_LIGHT)); 

  Serial.print(F("STORAGE_LIGHT status: "));
  Serial.println(BB_READ(LightPack, BB_STORAGE_LIGHT)); 

  Serial.print(F("USB-POWER status: "));
  Serial.println(BB_READ(LightPack, BB_USB_POWER)); 

  Serial.print(F("CPAP_POWER status: "));
  Serial.println(BB_READ(LightPack, BB_CPAP_POWER)); 

  Serial.println(F("====================="));
}
