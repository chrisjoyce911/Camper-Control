/*
  Software serial multple serial test

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 */
//#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"
#include "LiquidCrystal.h"


RTC_DS1307 RTC;
LiquidCrystal lcd(38, 39, 40, 41, 42, 43);


// SerailHandler
boolean newData = false;
const byte numChars = 254;
char receivedChars[numChars];
char tempChars[numChars];

struct DATA_STRUCTURE {
  bool NIGHT_LIGHT ;
  bool MAIN_LIGHT ;
  bool BED_LIGHT ;
  bool KITECHEN_LIGHT ;
  bool TRAILER_LIGHT ;
  bool STORAGE_LIGHT ;
  bool USB_POWER ;
  bool CPAP_POWER ;
};


struct DATA_STRUCTURE_LIGHT{
  char type[5];
  int messageID ;
  int lightbit ;
  bool lightstate ;
  int checksum ;
};
DATA_STRUCTURE_LIGHT rxlight;


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

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

byte LightPack = 0;
byte ButtonStatePack = 0;
byte LastButtonStatePack = 0;

bool StatusChange = 0 ;
int myRandom = 0 ;
int updatetime = 0 ;
bool HeartBeat = 0 ;

int BrightnessPin = 44 ;
int LCDbrightness = 130;

int NIGHT_LIGHT = 30 ;
int MAIN_LIGHT = 31 ;
int BED_LIGHT = 32 ;
int KITECHEN_LIGHT = 33 ;

int BUT_NIGHT_LIGHT = 22 ;
int BUT_MAIN_LIGHT = 23 ;
int BUT_BED_LIGHT = 24 ;
int BUT_KITECHEN_LIGHT = 25 ;
int BUT_TRAILER_LIGHT = 26 ;
int BUT_STORAGE_LIGHT = 27 ;
int BUT_USB_POWER = 28 ;
int BUT_CPAP_POWER = 29 ;

// D13 - LED
// D20 - SDA RTC
// D21 - SCL RTC

// D22 - BUT_NIGHT_LIGHT
// D23 - BUT_MAIN_LIGHT
// D24 - BUT_BED_LIGHT
// D25 - BUT_KITECHEN_LIGHT
// D26 - BUT_TRAILER_LIGHT
// D27 - BUT_STORAGE_LIGHT
// D28 - BUT_USB_POWER
// D29 - BUT_CPAP_POWER

// D30 - Relay 1
// D31 - Relay 2
// D32 - Relay 3
// D33 - Relay 4

// D38 - lcd(RS)
// D39 - lcd(E)
// D40 - lcd(D4)
// D41 - lcd(D5)
// D42 - lcd(D6)
// D43 - lcd(D7)
// D44 - lcd(Brightness)

// D52 - Software Serial RX
// D53 - Software Serial TX


//HardwareSerial & mySerial = Serial1;
//SoftwareSerial mySerial(52, 53); // RX, TX


void setup() {
  pinMode(BrightnessPin, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(NIGHT_LIGHT, OUTPUT);
  pinMode(MAIN_LIGHT, OUTPUT);
  pinMode(BED_LIGHT, OUTPUT);
  pinMode(KITECHEN_LIGHT, OUTPUT);

  pinMode(BUT_NIGHT_LIGHT, INPUT_PULLUP) ;
  pinMode(BUT_MAIN_LIGHT, INPUT_PULLUP) ;
  pinMode(BUT_BED_LIGHT, INPUT_PULLUP) ;
  pinMode(BUT_KITECHEN_LIGHT, INPUT_PULLUP) ;
  pinMode(BUT_TRAILER_LIGHT, INPUT_PULLUP) ;
  pinMode(BUT_STORAGE_LIGHT, INPUT_PULLUP) ;
  pinMode(BUT_USB_POWER, INPUT_PULLUP) ;
  pinMode(BUT_CPAP_POWER, INPUT_PULLUP) ;

  // Start LCD
  lcd.begin(20, 4);
  refreshDisplay("") ;

  Serial.begin(57600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
    
  BB_FALSE(LightPack, BB_NIGHT_LIGHT );
  BB_FALSE(LightPack, BB_MAIN_LIGHT);
  BB_FALSE(LightPack, BB_BED_LIGHT);
  BB_FALSE(LightPack, BB_KITECHEN_LIGHT);
  BB_FALSE(LightPack, BB_TRAILER_LIGHT);
  BB_FALSE(LightPack, BB_STORAGE_LIGHT);
  BB_FALSE(LightPack, BB_USB_POWER);
  BB_FALSE(LightPack, BB_CPAP_POWER);

  BB_FALSE(LastButtonStatePack, BB_NIGHT_LIGHT );
  BB_FALSE(LastButtonStatePack, BB_MAIN_LIGHT);
  BB_FALSE(LastButtonStatePack, BB_BED_LIGHT);
  BB_FALSE(LastButtonStatePack, BB_KITECHEN_LIGHT);
  BB_FALSE(LastButtonStatePack, BB_TRAILER_LIGHT);
  BB_FALSE(LastButtonStatePack, BB_STORAGE_LIGHT);
  BB_FALSE(LastButtonStatePack, BB_USB_POWER);
  BB_FALSE(LastButtonStatePack, BB_CPAP_POWER);
  
  showStatus();
  mytime();

  Serial1.begin(9600); 

  refreshDisplay("lights") ;

}

void loop() { // run over and over
  
   if(StatusChange){
      Serial.println(F("Sending New Light Settings"));
      StatusChange = 0 ;
   } 

    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
        parseData();
        // showParsedData();
        newData = false;
    }

    // setRelays();
    // maintainDisplay() ;
    
  if ( updatetime >  1000 ) {
      maintainDisplay() ;
      updatetime = 0 ;
  }
  updatetime++ ;

  CheckLightButtons () ;

}



void setRelays() {
  digitalWrite(NIGHT_LIGHT, BB_READ(LightPack, BB_NIGHT_LIGHT)) ; 
  digitalWrite(MAIN_LIGHT, BB_READ(LightPack, BB_MAIN_LIGHT)) ; 
  digitalWrite(BED_LIGHT, BB_READ(LightPack, BB_BED_LIGHT)) ; 
  digitalWrite(KITECHEN_LIGHT, BB_READ(LightPack, BB_KITECHEN_LIGHT)) ;
  mytime();
  showStatus(); 
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

