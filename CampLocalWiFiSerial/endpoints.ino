void toggleNetwork(){

  Serial.println("toggleNetwork");
  
  wifiap = !wifiap;

  getreply() ;
  server.send(200, "text/html",  message );
  
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);

  if (wifiap) {
    Serial.println("Switching to Access Point");
    WiFiAP();
  } else {
    Serial.println("Switching to Network Client");
    WiFiNetwork();
  }

  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}
  

void getStatus(){
  Serial.println("getStatus");
  sendalllights();
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
  showStatus();
}

void NIGHT_LIGHT(){
  Serial.println("NIGHT_LIGHT");
  BB_TOGGLE(LightPack, BB_NIGHT_LIGHT );
  sendlight(BB_NIGHT_LIGHT);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void MAIN_LIGHT(){
  Serial.println("MAIN_LIGHT");
  BB_TOGGLE(LightPack, BB_MAIN_LIGHT );
  sendlight(BB_MAIN_LIGHT);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void BED_LIGHT(){
  Serial.println("BED_LIGHT");
  BB_TOGGLE(LightPack, BB_BED_LIGHT );
  sendlight(BB_BED_LIGHT);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void KITECHEN_LIGHT(){
  Serial.println("KITECHEN_LIGHT");
  BB_TOGGLE(LightPack, BB_KITECHEN_LIGHT );
  sendlight(BB_KITECHEN_LIGHT);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void TRAILER_LIGHT(){
  Serial.println("TRAILER_LIGHT");
  BB_TOGGLE(LightPack, BB_TRAILER_LIGHT );
  sendlight(BB_TRAILER_LIGHT);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void STORAGE_LIGHT(){
  Serial.println("STORAGE_LIGHT");
  BB_TOGGLE(LightPack, BB_STORAGE_LIGHT );
  sendlight(BB_STORAGE_LIGHT);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void USB_POWER(){
  Serial.println("USB_POWER");
  BB_TOGGLE(LightPack, BB_USB_POWER );
  sendlight(BB_USB_POWER);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void CPAP_POWER(){
  Serial.println("CPAP_POWER");
  BB_TOGGLE(LightPack, BB_CPAP_POWER );
  sendlight(BB_CPAP_POWER);
  getreply() ;
  server.send(200, "text/html",  message );
  Serial.println("Client servied");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

