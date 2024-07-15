/* Last Update 071424-02*/
const char* dweetsite = "dweet.io";
int stopval = 1;

void dweetdata() {
  WiFiClient client; 
  const int httpPort = 80; 
  if (!client.connect(dweetsite, httpPort)) { 
    Serial.println("connection failed"); 
    return; 
    } 
  int turbidityLevel = analogRead(A0);
  String dweetstring="GET /dweet/for/";
  dweetstring=dweetstring+String(DWEET_THING)+"?water_level="+String(waterLVL)+"&turbidity="+String(turbidityLevel)+"&temp="+String(tempF)+"&humidity="+String(humid)+"&TDS="+String(tds)+"&PH="+String(phLvl)+"&bubbler="+String(bubbler)+"&p1="+String(p1)+"&p2="+String(p2)+"&p3="+String(p3)+"&p4="+String(p4);
  Serial.println(dweetstring);

  dweetstring=dweetstring+" HTTP/1.1\r\n"+
      "Host: " + 
      dweetsite + 
      "\r\n" + 
      "Connection: close\r\n\r\n";
    
  client.print(dweetstring); 
  delay(10);//wait a bit for stability 

  while(client.available()){ 
    String line = client.readStringUntil('\r'); 
    Serial.print(line); 
    } 
  Serial.println("Dweet Posted");
}
