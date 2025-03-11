#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

// WiFi Credentials
const char* ssid = "bhavi";
const char* password = "bhavithran";
const char* server = "http://hydroponics.quantumard.com/update_data.php";
const char* motorStateURL = "http://hydroponics.quantumard.com/motor_state.txt";

// Sensor & Relay Pins
#define DHTPIN 2        // D4 on ESP8266
#define DHTTYPE DHT11
#define SOIL_SENSOR A0
#define PIR_SENSOR 14   // D5
#define RELAY_PIN 0     // D3

DHT dht(DHTPIN, DHTTYPE);
int relayState = 0;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Initialize Sensors
  dht.begin();
  pinMode(SOIL_SENSOR, INPUT);
  pinMode(PIR_SENSOR, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  // Read Sensor Data
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soil = analogRead(SOIL_SENSOR);
  soil = map(soil, 0, 1024, 0, 100);
  soil = (100 - soil);
  int motion = digitalRead(PIR_SENSOR);
  
  Serial.print("Temp: "); Serial.print(temp); Serial.print("°C, ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.print("%, ");
  Serial.print("Soil Moisture: "); Serial.print(soil); Serial.print("%, ");
  Serial.print("Motion: "); Serial.println(motion);
  
  // Send Data to Server
  sendData(temp, humidity, soil, motion);

  // Fetch Motor State from Server
  fetchMotorState();

  delay(5000);
}

// Function to Send Data to PHP Server
void sendData(float temp, float humidity, int soil, int motion) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String url = String(server) + "?temp=" + String(temp) +
                 "&humidity=" + String(humidity) +
                 "&soil=" + String(soil) +
                 "&motion=" + String(motion);
    
    http.begin(client, url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Data sent successfully!");
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpCode);
    }
    
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}

// Function to Fetch Motor State from Server
void fetchMotorState() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, motorStateURL);
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      relayState = payload.toInt();
      digitalWrite(RELAY_PIN, relayState);
      Serial.print("Motor State: ");
      Serial.println(relayState);
    } else {
      Serial.print("Failed to fetch motor state: ");
      Serial.println(httpCode);
    }

    http.end();
  }
}
