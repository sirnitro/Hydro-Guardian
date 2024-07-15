/* Last Update 071424-02 */
#include "pvt.h"
#include "DHT.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "WiFiS3.h"

/* H20 LEVEL */
#define h20LevelSensorPower 6
#define h20LevelSensorPin A1
int waterLVL = 3;

/*WIFI*/
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;

/* DHT*/
#define DHTPIN 7    
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

/* DWEET TEST VARS */
String tempF = "79";
String humid = "74";
String tds = "TBD";
String phLvl = "PHTBD";
String bubbler = "TBD";
String p1 = "On";
String p2 = "On";
String p3 = "On";
String p4 = "On";
/* END DWEET TEST VARS*/

#include "functions.h"
#include "matrixFunctions.h"
#include "dweet.h"


void setup(){
  Serial.begin(9600);

  matrix.loadSequence(LEDMATRIX_ANIMATION_WIFI_SEARCH);
  matrix.begin();
  matrix.play(true);

  delay(2500);

  dht.begin();
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW);

  pinMode(h20LevelSensorPower, OUTPUT);	
	digitalWrite(h20LevelSensorPower, LOW); 


  /* WIFI */
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  matrixScroll("Connected to Wifi");
  printWifiStatus();
  Serial.print("Firmware Ver.: ");
  Serial.println(fv);
  
  matrixScroll("Intializing the Matrix");
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS);
  matrix.begin();
  matrix.play(true);
  delay(5000);

}

void loop() {

  matrixScroll("Checking Temp & Humidity");
  dhtSensor();
  delay(5000);

  matrixScroll("Checking Turbidity");
  int turbidityLevel = analogRead(A0);
  turbidity();
  delay(5000);

  matrixScroll("Checking Water Level");
  waterLvl();
  delay(5000);

  matrixScroll("Dweeting");
  dweetdata();
  delay(5000);


}



/* Last Update 071424 */


