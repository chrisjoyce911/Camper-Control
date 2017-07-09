

void sendlight(int light ) {
  // <LIGHT,89,128,1,85>
  String myMessage ;
  myMessage = "LIGHT,89," ;
  myMessage = myMessage + light + ",";
  myMessage = myMessage + BB_READ(LightPack, light) + "," ;
  myMessage = myMessage + generateCheckSum(myMessage) ;
  myMessage = "<" + myMessage + ">\n" ;
  StatusChange = 1 ;
}


void sendalllights() {
  
}

