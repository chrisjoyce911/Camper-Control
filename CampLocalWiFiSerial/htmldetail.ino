
void setheader(){
  HTMLheader = "<head><title>Camper Control</title>\n";
  HTMLheader += "<meta name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0;\">\n";
  HTMLheader += "<style type=\"text/css\">\n";
  HTMLheader += "body {background:#0B3954;font-family: Helvetica;color:#999;}\n";
  HTMLheader += "p {font-size:32px;padding-bottom:8px;}\n";
  HTMLheader += "a {color:#FF6663;text-decoration:none;}\n";
  HTMLheader += "h1 {ont-size:45px;display:block;75%;height:41px;}\n";
  HTMLheader += "#page_wrapper {padding-top:5px;overflow:auto;}\n";

  HTMLheader += ".button {\n";
  HTMLheader += "display: inline-block;\n";
  HTMLheader += "position: relative;\n";
  HTMLheader += "width: 60%;\n";
  HTMLheader += "color: #FF6663;\n";
  HTMLheader += "text-shadow: 0 1px 0 rgba(255,255,255, 0.8);\n";
  HTMLheader += "text-decoration: none;\n";
  HTMLheader += "text-align: center;\n";
  HTMLheader += "padding: 8px 12px;\n";
  HTMLheader += "font-size: 32px;\n";
  HTMLheader += "font-weight: 700;\n";
  HTMLheader += "font-family: helvetica, arial, sans-serif;\n";
  HTMLheader += "border-radius: 4px;\n";
  HTMLheader += "border: 1px solid #bcbcbc;\n";
  HTMLheader += "-webkit-box-shadow: 0 1px 3px rgba(0,0,0,0.12);\n";
  HTMLheader += "box-shadow: 0 1px 3px rgba(0,0,0,0.12);\n";
  HTMLheader += "background-image: -webkit-linear-gradient(top, rgba(255,255,255,1) 0%,rgba(239,239,239,1) 60%,rgba(225,223,226,1) 100%);\n";
  HTMLheader += "}\n";

  HTMLheader += "</style></head><body><center>\n";
  HTMLheader += "<div id=\"page_wrapper\">\n";
  HTMLheader += "<h1>Camper Control</h1>\n";
}

void setfooter(){
  HTMLfooter = "</div></center></body>";
}

void setbody(){
  String ledmessage ;
  String stylecolour ;
  HTMLbody = "";
  
  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_NIGHT_LIGHT))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/NIGHT_LIGHT\" class=\"button\" " + stylecolour + ">Turn NIGHT_LIGHT "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_MAIN_LIGHT))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/MAIN_LIGHT\" class=\"button\" " + stylecolour + ">Turn MAIN_LIGHT "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_BED_LIGHT))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/BED_LIGHT\" class=\"button\" " + stylecolour + ">Turn BED_LIGHT "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_KITECHEN_LIGHT))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/KITECHEN_LIGHT\" class=\"button\" " + stylecolour + ">Turn KITECHEN_LIGHT "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_TRAILER_LIGHT))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/TRAILER_LIGHT\" class=\"button\" " + stylecolour + ">Turn TRAILER_LIGHT "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_STORAGE_LIGHT))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/STORAGE_LIGHT\" class=\"button\" " + stylecolour + ">Turn STORAGE_LIGHT "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_USB_POWER))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/USB_POWER\" class=\"button\" " + stylecolour + ">Turn USB_POWER "+ ledmessage +"</a></p>\n";

  ledmessage = "On";
  stylecolour= " style=\"color: #A7BE3B\" ";
  if (BB_READ(LightPack, BB_CPAP_POWER))
  {
    ledmessage = "Off";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/CPAP_POWER\" class=\"button\" " + stylecolour + ">Turn CPAP_POWER "+ ledmessage +"</a></p>\n";
  
  HTMLbody += "<p><a href=\"/status\" class=\"button\" >Update Status</a></p>\n";
  
  ledmessage = "Change to Network Client";

  if (wifiap)
  {
    ledmessage = "Change to Access Point";
    stylecolour= " style=\"color: #FF6663\" ";
  }
  HTMLbody += "<p><a href=\"/setnetwork\" class=\"button\" " + stylecolour + ">"+ ledmessage +"</a></p>\n";
  
 }

 void getreply(){
  setheader() ;
  setbody() ;
  setfooter() ;
  message =  HTMLheader + HTMLbody + HTMLfooter ;
  // showStatus();
 }

