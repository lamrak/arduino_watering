#include <SPI.h>
#include <WiFi.h>

#define PUMP_PIN 4
#define MOISTURE_PIN A0
#define LIGHT_PIN A1
#define LEVEL_PIN A2

#define WATERING_MILLIS 2000

#define STATE_STANDBY 0
#define STATE_WATERING 1
#define STATE_NOWATER 2
#define STATE_SENDPAGE 3

#define WEB_NO_CLIENT 0
#define WEB_FORCED_WATERING 1
#define WEB_CLIMATE_REQUEST 2

#define HALF_WATER_TANK 900
#define CRITICAL_WATER_LEVEL 600

WiFiServer server(81);

String url;
String request;
String json;

int state = STATE_STANDBY;
int wifiStatus = WL_IDLE_STATUS;

int moistureValue;
int temperatureValue;
int lightnessValue;
int levelValue;
  
boolean gotWater;


void setup() {
  Serial.begin(9600);
  pinMode(MOISTURE_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(LEVEL_PIN, OUTPUT);
  
  connectToWiFi();                     
}

void connectToWiFi() {
  isWiFiEnabled(); 
  checkFirmwareVersion();
  attemptToConnect();
  startWebServer();
  printWifiStatus();  
}

void loop() {
  checkServerRequest();
}

void watering() {
  Serial.println("Watering"); 
//  digitalWrite(PUMP_PIN, LOW);
//  delay(WATERING_MILLIS);
//  digitalWrite(PUMP_PIN, HIGH);
}

boolean checkClimate() {
  Serial.println("Read climat detectors"); 
  moistureValue = analogRead(MOISTURE_PIN);
//  temperatureValue = analogRead(TEMP_PIN);
  levelValue = analogRead(LEVEL_PIN);
  lightnessValue = analogRead(LIGHT_PIN);

  json = "";
  json += "{\"moistureValue\":\"";
  json += moistureValue;
  json += "\",\"temperatureValue\":\"0\"";
  json += ",\"lightnessValue\":\"";
  json += lightnessValue;
  json += "\",\"levelValue\":\"";
  json += levelValue;
  json += "\"}";

  Serial.println(json); 

  return true;
}

boolean checkWater() {
//  Serial.print("Check Water: ");
  levelValue = analogRead(LEVEL_PIN);
//  Serial.print(levelValue);
//  Serial.println("");

  if ((levelValue > HALF_WATER_TANK) || 
      (levelValue > CRITICAL_WATER_LEVEL))
    gotWater = true;
  else
    gotWater = false;

  return gotWater; //gotWater;
}

int checkServerRequest() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            prepareSendPage(client);
            break;         
          } else currentLine = "";
        } else if (c != '\r') {   
          currentLine += c;
        }

        if (currentLine.endsWith("GET /W")) {
          watering();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void prepareSendPage(WiFiClient client) {
  checkClimate();
  sendPage(client);
}

void sendPage(WiFiClient client) {
  Serial.println("Send Page");

  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:    
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println(json);
  client.println();
  delay(1);
}

void isWiFiEnabled() {
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);
  }
}

void checkFirmwareVersion() {
  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
}

void attemptToConnect() {
  char ssid[] = "Valtech_";
  char pass[] = "2015Valtech";
  while (wifiStatus != WL_CONNECTED) { 
    Serial.println("Attempting to connect to Network...");  
    wifiStatus = WiFi.begin(ssid, pass);
    delay(10000);
  } 
}

void startWebServer() {
  server.begin();
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("signal strength (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  
  url = "http://192.168.10.76:81/";
}

/* *
- Soggy soil -  moisture between 0 and 500;
- Wet soil   - moisture between 500 and 800;
- Dry soil   - moisture between 800-1023;
 */
String getStringForMoistureValue() {
  if (moistureValue > 950)
    return "Critical Dry soil";
  if (moistureValue > 850)
    return "Dry soil";
  if (moistureValue > 800)
    return "Partially dry soil";
  if (moistureValue > 700)
    return "Partially wet soil";
  if (moistureValue > 600)
    return "Normal Wet soil";
  if (moistureValue > 500)
    return "Strong Wet soil";
  if (moistureValue > 400)
    return "Soggy soil";
  if (moistureValue > 200)
    return "Like a swamp in the pot";
  if (moistureValue > 0)
    return "Like a ocean in the pot";
}

String getLightnessAsString() {
  if (lightnessValue > 1000)
    return "Night time";
  if (lightnessValue > 800)
    return "Gray: cloudly or morning/evening";
  if (moistureValue > 600)
    return "Day light";
  if (moistureValue > 0)
    return "Sunshine";
}
