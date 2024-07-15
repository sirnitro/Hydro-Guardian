/* Last Update 071424-02 */
void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void dhtSensor(){
  float h = dht.readHumidity();       
  float c = dht.readTemperature();        // Read temperature as Celsius (the default)
  float f = dht.readTemperature(true);    // Read temperature as Fahrenheit (isFahrenheit = true)
  float hif = dht.computeHeatIndex(f, h);       // Compute heat index in Fahrenheit (the default)
  float hic = dht.computeHeatIndex(c, h, false);     // Compute heat index in Celsius (isFahreheit = false)

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(c);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void turbidity(){
  
  int turbidityLevel = analogRead(A0);
  Serial.print("Turbidity Level: ");
  Serial.println(turbidityLevel);
}


void waterLvl(){
  digitalWrite(h20LevelSensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	waterLVL = analogRead(h20LevelSensorPin);		// Read the analog value form sensor
	digitalWrite(h20LevelSensorPower, LOW);		// Turn the sensor OFF
	Serial.println(waterLVL);
}


