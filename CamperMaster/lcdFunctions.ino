

void maintainDisplay()
{
  static const unsigned long REFRESH_INTERVAL = 1000; // ms
  static unsigned long lastRefreshTime = 0;
  
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
          digitalWrite(LED_BUILTIN, HeartBeat) ;
      HeartBeat = !HeartBeat ;
      
    lastRefreshTime += REFRESH_INTERVAL;
                refreshDisplay("lights");
  }
}



void refreshDisplay(String format) {

  analogWrite(BrightnessPin, LCDbrightness);

  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print("Camper Control");
  // set cusor position to start of next line
  lcd.setCursor(15,0);
  lcd.print(getTime());

  if (format == "lights") {
    lcd.setCursor(0,1);
    if (BB_READ(LightPack, BB_NIGHT_LIGHT)){
    lcd.print("Night");
    }
    
    lcd.setCursor(10,1);
    if (BB_READ(LightPack, BB_MAIN_LIGHT)){
    lcd.print("Main");
    }

    lcd.setCursor(0,2);
    if (BB_READ(LightPack, BB_BED_LIGHT)){
    lcd.print("Bed");
    }
    
    lcd.setCursor(10,2);
    if (BB_READ(LightPack, BB_KITECHEN_LIGHT)){
    lcd.print("Kitchen");
    }    
    lcd.setCursor(0,3);
    if (BB_READ(LightPack, BB_USB_POWER)){
    lcd.print("USB");
    }
    
    lcd.setCursor(10,3);
    if (BB_READ(LightPack, BB_CPAP_POWER)){
    lcd.print("CPAP");
    } 
  }
 }

