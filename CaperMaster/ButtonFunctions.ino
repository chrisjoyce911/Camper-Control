
void buttonPress(int ThisButton) {

  if (!BB_READ(LastButtonStatePack, ThisButton)) {
    BB_TRUE(LastButtonStatePack, ThisButton);
    BB_TOGGLE(LightPack, ThisButton );
    StatusChange = 1 ;
    setRelays();
    maintainDisplay() ;  
  }

}

void CheckLightButtons () {
   if (!digitalRead(BUT_NIGHT_LIGHT)) {
    buttonPress(BB_NIGHT_LIGHT) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_NIGHT_LIGHT);
  }
  if (!digitalRead(BUT_MAIN_LIGHT)) {
    buttonPress(BB_MAIN_LIGHT) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_MAIN_LIGHT);
  }
  if (!digitalRead(BUT_BED_LIGHT)) {
    buttonPress(BB_BED_LIGHT) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_BED_LIGHT);
  }
  if (!digitalRead(BUT_KITECHEN_LIGHT)) {
    buttonPress(BB_KITECHEN_LIGHT) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_KITECHEN_LIGHT);
  }
  if (!digitalRead(BUT_TRAILER_LIGHT)) {
    buttonPress(BB_TRAILER_LIGHT) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_TRAILER_LIGHT);
  }
  if (!digitalRead(BUT_STORAGE_LIGHT)) {
    buttonPress(BB_STORAGE_LIGHT) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_STORAGE_LIGHT);
  }
  if (!digitalRead(BUT_USB_POWER)) {
    buttonPress(BB_USB_POWER) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_USB_POWER);
  }
  if (!digitalRead(BUT_CPAP_POWER)) {
    buttonPress(BB_CPAP_POWER) ;
  } else {
    BB_FALSE(LastButtonStatePack, BB_CPAP_POWER);
  }
}

