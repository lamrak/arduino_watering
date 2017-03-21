#include <SPI.h>
#include <WiFi.h>

#define PUMP_PIN 7
#define MOISTURE_PIN A0
#define LIGHT_PIN A1
#define LEVEL_PIN A2

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
WiFiClient client;

String url;
String request;

int state = STATE_STANDBY;
int wifiStatus = WL_IDLE_STATUS;

int moistureValue;
int temperatureValue;
int lightnessValue;
int levelValue;
  
boolean gotWater;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOISTURE_PIN, INPUT);
  
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
  switch (state) {
    case STATE_STANDBY:
      if (webRequest() == 1 && gotWater)
        state = STATE_WATERING;
      else if (webRequest() == 2)
        state = STATE_SENDPAGE;
      if (!gotWater)
        state = STATE_NOWATER;
      break;
      
    case STATE_WATERING:
        watering();
        state = STATE_STANDBY;
      break;
      
    case STATE_NOWATER:
      if (webRequest() == WEB_CLIMATE_REQUEST)
        state = STATE_SENDPAGE;
      else if (checkWater())
        state = STATE_STANDBY;
      break;
      
    case STATE_SENDPAGE:
      sendPage();
      state = STATE_STANDBY;
      break;
  }
}

void watering() {
  Serial.println("Watering"); 
//  digitalWrite(PUMP_PIN, HIGH);
//  delay(WATERING_MILLIS);
//  digitalWrite(PUMP_PIN, LOW);
}

boolean checkClimate() {
  Serial.println("Read climat detectors"); 
  moistureValue = analogRead(MOISTURE_PIN);
//  temperatureValue = analogRead(TEMP_PIN);
  lightnessValue = analogRead(LIGHT_PIN);
}

boolean checkWater() {
    levelValue = analogRead(LEVEL_PIN);
//  digitalWrite(WATER_OUT_PIN, LOW);
  if (levelValue > HALF_WATER_TANK)
    gotWater = true;
  else if (levelValue > CRITICAL_WATER_LEVEL)
    gotWater = true;
  else
    gotWater = false;
//  digitalWrite(WATER_OUT_PIN, HIGH);

  return gotWater; //gotWater;
}

int webRequest() {
  Serial.println("Web Request"); 
  client = server.available();
  request = "";

  if (client) {
    Serial.println("new client");
    String currentLine = "";
    boolean currentLineIsBlank = false;
          
    while (client.connected()) {
      
      if (client.available()) {
        char c = client.read();

        if (request.length() < 100)
          request += c;
        if (request.indexOf("?water") > 0)
          return WEB_FORCED_WATERING;
        if (c == '\n')
          currentLineIsBlank = true;
        else if (c != '\r')
          currentLineIsBlank = false;
        if (c == '\n' && currentLineIsBlank)
          return WEB_CLIMATE_REQUEST;
      }
    }
    
    delay(1);
    client.stop();
    Serial.println("client disonnected");
  }

  return WEB_NO_CLIENT;
}

void sendPage()
{
  if (client) {
    while (client.connected()) {
      Serial.println("Print html page");
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");  
      client.println("Refresh: 5;url=\"http://192.168.0.150\"");  
      client.println();
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("Moisture humidity: ");
      client.println(getStringForMoistureValue());
//      client.println("<br />Temperature: ");
//      client.println(temperatureValue);
      client.println("<br />Lightness: ");
      client.println(getLightnessAsString());
      if (gotWater) {
        client.println("<br />Water ok<br />");
        client.println("<a href=\"/?water\"\">Forced watering</a>");
      } else {
        client.println("No water!");
      }
      
      client.println("</html>");
      break;
    }
  }

  delay(1);
  client.stop();
  Serial.println("client disonnected");
}

void isWiFiEnabled() {
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);
  }
}

void checkFirmwareVersion() {
  if (WiFi.firmwareVersion() != "1.1.0")
    Serial.println("Please upgrade the firmware");
}

void attemptToConnect() {
  char ssid[] = "Valtech_";
  char pass[] = "2015Valtech";
  while (wifiStatus != WL_CONNECTED) { 
    Serial.print("Attempting to connect to Network...");  
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
  
  url = "http://192.168.11.117:81";
}

/* *
- Soggy soil -  moisture between 0 and 500;
- Wet soil   - moisture between 500 and 800;
- Dry soil   - moisture between 800-1023;
 */
String getStringForMoistureValue() {
  if (moistureValue > 950)
    return "Like a ocean in the pot";
  if (moistureValue > 850)
    return "Like a swamp in the pot";
  if (moistureValue > 800)
    return "Soggy soil";
  if (moistureValue > 700)
    return "Strong Wet soil";
  if (moistureValue > 600)
    return "Normal Wet soil";
  if (moistureValue > 500)
    return "Partially wet soil";
  if (moistureValue > 400)
    return "Partially dry soil";
  if (moistureValue > 200)
    return "Dry soil";
  if (moistureValue > 0)
    return "Critical Dry soil";
}

String getLightnessAsString() {
  if (lightnessValue > 900)
    return "Night time";
  if (lightnessValue > 700)
    return "Gray: cloudly or morning/evening";
  if (moistureValue > 400)
    return "Day light";
  if (moistureValue > 0)
    return "Sunshine";
}
