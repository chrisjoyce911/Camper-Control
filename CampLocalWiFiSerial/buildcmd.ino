

void sendpackets() {
  String processs ;
  int i ;
  int sendThis ; 
  if(StatusChange ){
    sendThis = findNextPacket() ;
  }
   if(StatusChange ){
      if (sendThis < ARRAYSIZE +1 ) {
        processs = outmessage[sendThis] ;
       //  Serial.print(F("Sending packet :"));
  
        char charBuf[processs.length()];
        processs.toCharArray(charBuf, processs.length());
 
        for (i = 0; i < sizeof(charBuf)  ; i++){
          mySerial.write(charBuf[i]);
        }
        outmessage[sendThis] = "" ;
       //  Serial.println(charBuf);
      }
      delay(25) ;
   } 
   
}

int findNextPacket() {
  int sendThis = 10 ;
  bool packetsToSend = 0 ;
  int i ;
  for (i = 0; i < ARRAYSIZE  ; i++){
    if (outmessage[i].length() > 1) {
      sendThis = i ;
      packetsToSend = 1 ;
      i = ARRAYSIZE ;
    }
  }

  if (packetsToSend) {
    StatusChange = 1 ;
    // Serial.print("Packet found at :");
    // Serial.println(sendThis);
  } else {
    StatusChange = 0 ;
    // Serial.println("NO packets found");
  }
  
  return sendThis ;
}
void addNewPacket(String packet) {
  int i ;
  for (i = 0; i < ARRAYSIZE  ; i++){
    if (outmessage[i].length() < 1) {
      outmessage[i] = packet ;
      // Serial.print(F("Packet added at :"));
      // Serial.println(i);
      i = ARRAYSIZE ;
    }
  }
  StatusChange = 1 ;
}


String getnextmessageid() {

  String tmpID = "0000";
  messageID++ ;
  if( messageID > 9999 ){
    messageID = 1 ;
  }

  tmpID = tmpID + messageID ;
  tmpID = tmpID.substring(tmpID.length()-4, tmpID.length()) ;

  // Serial.print(F("messageID : "));
  // Serial.println(tmpID);
  return tmpID ;
  
}


void sendlight(int light ) {
  // <LIGHT,89,128,1,85>
  String myMessage ;
  myMessage = "LIGHT,"+ getnextmessageid() +"," ;
  myMessage = myMessage + light + ",";
  myMessage = myMessage + BB_READ(LightPack, light) + "," ;
  myMessage = myMessage + generateCheckSum(myMessage) ;
  addNewPacket( "<" + myMessage + ">\n" );
}


void sendalllights() {
  sendlight(BB_NIGHT_LIGHT);
  sendlight(BB_MAIN_LIGHT);
  sendlight(BB_BED_LIGHT);
  sendlight(BB_KITECHEN_LIGHT);
  sendlight(BB_TRAILER_LIGHT);
  sendlight(BB_STORAGE_LIGHT);
  sendlight(BB_USB_POWER);
  sendlight(BB_CPAP_POWER);
}


void keepAlive()
{
    // <ALIVE,MID,cSum>
    String myMessage ;
    myMessage = "ALIVE,"+ getnextmessageid() +"," ;
    myMessage = myMessage + generateCheckSum(myMessage) ;
    addNewPacket( "<" + myMessage + ">\n" );
    updatetime = 0 ;
}
