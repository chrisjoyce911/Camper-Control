void parseData() {

  if (testCheckSum(tempChars)) {
    Serial.println();
    Serial.println(tempChars);
    Serial.println("Check sum was a match now process !");

    char * strtokIndx;
    String messageType ;
        
    strtokIndx = strtok(tempChars,",");
    messageType = String(strtokIndx);

    Serial.print("Message Type : ");
    Serial.println(messageType);
   
  
    if ( messageType == "LIGHT" ) {
    
      strcpy(rxlight.type, strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      rxlight.messageID = atoi(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      rxlight.lightbit = atoi(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      rxlight.lightstate = atoi(strtokIndx);
      
      strtokIndx = strtok(NULL, ",");
      rxlight.checksum = atoi(strtokIndx);
      parseLightData() ;
      
    } else if (messageType == "RUCMD") {

      strtokIndx = strtok(NULL, ",");
      int messageID = atoi(strtokIndx);

      char tmpCommand[32] ;
      strtokIndx = strtok(NULL,",");
      strcpy(tmpCommand, strtokIndx) ; 
      runcommand(String(tmpCommand));

    } else if (messageType == "INARG") {

      strtokIndx = strtok(NULL, ",");
      int messageID = atoi(strtokIndx);

      char tmpCommand[32] ;
      strtokIndx = strtok(NULL,",");
      strcpy(tmpCommand, strtokIndx) ; 

      strtokIndx = strtok(NULL,",");
      int intarg = atoi(strtokIndx);
      runcommandint(String(tmpCommand),intarg);

    } else {
  
      strtokIndx = strtok(NULL, ",");
    //  rxdata.messageID = atoi(strtokIndx);
   
      strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    //  integerFromSerial = atoi(strtokIndx);     // convert this part to an integer
  
      strtokIndx = strtok(NULL, ",");
    //  floatFromSerial = atof(strtokIndx);     // convert this part to a float
    }
  } else {
    Serial.println();
    Serial.println(tempChars);
    Serial.print("Check sum did not match should have been : ");
    Serial.println(generateCheckSum(removeCheckSum(tempChars)));
  }
}
