bool testCheckSum(String inString) {
  String strSentCheckSum = getChecksum(inString) ;
  String strGenCheckSum = generateCheckSum(removeCheckSum(inString)) ;
  int SentCheckSum  = strSentCheckSum.toInt() ;
  int GenCheckSum  = strGenCheckSum.toInt() ;

  if (SentCheckSum != GenCheckSum) {
    return 0 ;
  } else {
    return 1 ;
  } 
  
}

String removeCheckSum(String inString) {
  inString.remove(inString.length() - 2, 2);
  return inString ;
}


String generateCheckSum(String inString){
   
  int cSum = checkSum(inString.length(),inString);
  String mycSum ;
  if (cSum<10) {
    mycSum = '0' + String(cSum) ;
  } else {
    mycSum = String(cSum) ;
  }
  return mycSum  ;
}

String getChecksum(String inString) {
  int strtofcSum = inString.length() - 2 ;
  String testcSum = inString.substring(strtofcSum, inString.length()) ;
  return testcSum ;
}

int checkSum(int num , String inString){
  int XOR = 0;
  for(int i=0; i<(num); i++) {
    XOR = XOR ^ inString.charAt(i);
  }

  if (XOR > 99 ) {
    XOR = XOR - 100 ;
  }
  return XOR;
}
