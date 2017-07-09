


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial3.available() > 0 && newData == false) {
        rc = Serial3.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
                
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
                
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }

  
}


void runcommandint(String function , int i) {
 Serial.print("COMMAND MESSAGE : ");
 Serial.println(function); 
 
 Serial.print("Int arg : ");
 Serial.println(i); 
 
  if (function == "mydelay") {
    mydelay(i);
  }
  
}

void runcommand(String function) {
 Serial.print("COMMAND MESSAGE : ");
 Serial.println(function); 

  if (function == "ledon") {
    ledon();
  }

  if (function == "ledoff") {
    ledoff();
  }
  
}

void ledon() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void ledoff() {
  digitalWrite(LED_BUILTIN, LOW);
}

void mydelay(int d) {
  delay(d);
}


void parseLightData() {

    Serial.println("LIGHT MESSAGE");
    Serial.print("Message ID :");
    Serial.println(rxlight.messageID);    
    Serial.print("Light Bit ");
    Serial.println(rxlight.lightbit);
    Serial.print("Light State ");
    Serial.println(rxlight.lightstate);
}


