#include <WiFiManager.h>               // WiFi Manager to handle Wi-Fi
#include <FS.h>                        // File System for SPIFFS
#include <SPIFFS.h>                    // SPIFFS library
#include <ESPAsyncWebServer.h>         // Web server library
#include <Ticker.h>                    // Ticker for interval tasks

// Relay configuration
#define RELAY_PIN 12                   // GPIO pin where relay is connected
bool relayState = false;               // Stores the state of the relay (on/off)
Ticker relayTicker;                    // Ticker for relay automation

// Timer interval (3 hours in milliseconds)
const long interval = 10800000;        // 3 hours = 3 * 60 * 60 * 1000 ms
const long relayDuration = 600000;     // 10 minutes = 10 * 60 * 1000 ms

// Web server
AsyncWebServer server(80);

// Function prototypes
void saveWiFiConfig();
void setupRelay();
void toggleRelay();
void autoRelayOn();
void autoRelayOff();
void handleRelayToggle(String action);

// Save WiFi credentials to SPIFFS
void saveWiFiConfig() {
  File file = SPIFFS.open("/wificonfig.txt", FILE_WRITE);
  if (file) {
    file.println(WiFi.SSID());
    file.println(WiFi.psk());
    file.close();
    Serial.println("WiFi credentials saved to SPIFFS");
  } else {
    Serial.println("Failed to save WiFi credentials");
  }
}

// Setup relay control
void setupRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);        // Relay is initially off
  relayState = false;
}

// Toggle the relay manually via the web interface
void toggleRelay() {
  relayState = !relayState;
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
  Serial.println(relayState ? "Relay ON" : "Relay OFF");
}

// Automatically turn on the relay
void autoRelayOn() {
  relayState = true;
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Relay activated (auto)");

  // Schedule the relay to turn off after 10 minutes
  relayTicker.once_ms(relayDuration, autoRelayOff);
}

// Automatically turn off the relay
void autoRelayOff() {
  relayState = false;
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay deactivated (auto)");
}

// Handle relay toggle via web interface
void handleRelayToggle(String action) {
  if (action == "on") {
    relayState = true;
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Relay turned ON via web interface");
  } else if (action == "off") {
    relayState = false;
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Relay turned OFF via web interface");
  }
}

void setup() {
  // Initialize Serial and SPIFFS
  Serial.begin(9600);
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  // Setup relay
  setupRelay();

  // Initialize WiFiManager
  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveWiFiConfig);
  
  // Try to auto-connect to saved network or start the config portal
  if (!wifiManager.autoConnect("ESP32_Relay_Control")) {
    Serial.println("Failed to connect to Wi-Fi, restarting...");
    ESP.restart();
  }

  Serial.println("Connected to Wi-Fi");

  // Start the web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><body><h1>Relay Control</h1>";
    html += "<p>Relay Status: " + String(relayState ? "ON" : "OFF") + "</p>";
    html += "<p><a href=\"/relay/on\"><button>Turn On</button></a></p>";
    html += "<p><a href=\"/relay/off\"><button>Turn Off</button></a></p>";
    request->send(200, "text/html", html);
  });

  server.on("/relay/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRelayToggle("on");
    request->redirect("/");
  });

  server.on("/relay/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRelayToggle("off");
    request->redirect("/");
  });

  server.begin();
  Serial.println("Web server started");

  // Start the auto relay on/off process with a 3-hour interval
  relayTicker.attach_ms(interval, autoRelayOn);
}

void loop() {
  // No code is needed in the loop since Ticker handles timing and the web server is asynchronous.
}
