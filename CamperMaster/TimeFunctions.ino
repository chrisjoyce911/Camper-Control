
String getTime() {
  DateTime now = RTC.now();

  String thehour = String(now.hour(), DEC);
  if (now.hour() < 10) {
    thehour = "0" + thehour ;
  }
  
  String themin = String(now.minute(), DEC);
  if (now.minute() < 10) {
    themin = "0" + themin ;
  }

  String dataString ;
  dataString = String(thehour + ":" + themin );
  return dataString ;
}


void mytime() {
    DateTime now = RTC.now(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); 
}
