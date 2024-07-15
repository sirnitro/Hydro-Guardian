//Code by Sir Nitro//

//const unsigned long onDurationMs = 5000; // 5 Seconds
//const unsigned long offDurationMs = 10000; // 10 Seconds
const unsigned long onDurationMs = 900000; // 15 Minutes
const unsigned long offDurationMs = 10800000; // 3 Hours
unsigned long onTimeMs = 0; //Used to keep track of on time for pump
unsigned long offTimeMs = 0; //Used to keep track of off time for pump
int pumpState = LOW; //Set pump to on to begin with
int relay = 12; // Plug the relay into Digital Pin 12

void setup(){
  Serial.begin(9600); //Enabling serial communication for debug purposes
  pinMode(relay, OUTPUT); //Setting the relay pin (12) to output mode
  pinMode(13, OUTPUT);    // sets the digital pin 13 as output
  Serial.println("Start Loop");
  digitalWrite(13, HIGH); // Turn Onboard LED On
  digitalWrite(relay, LOW); // Turn the relay on
}

void loop(){
  if( pumpState ==LOW){
    
    if( (millis()-onTimeMs) >= onDurationMs){
      pumpState = HIGH;
      digitalWrite(13, LOW); // Turn Onboard LED Off
      digitalWrite(relay, HIGH); // Turn the relay off
      offTimeMs=millis();
      Serial.println("Pump Turned Off");
    }
    
  }else if( pumpState ==HIGH){

    if( (millis()-offTimeMs) >= offDurationMs){
      pumpState= LOW;
      digitalWrite(13, HIGH);
      digitalWrite(relay, LOW);
      onTimeMs=millis();
      Serial.println("Pump Turned On");
    }

    
  }else{
    Serial.println("ERROR");
  }
}
