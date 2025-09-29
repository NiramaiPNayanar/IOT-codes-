#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid   = "<WIFI-NAME>";
const char* pass   = "<WIFI-PASSWORD>";
const char* server = "http://<ipv4 from ipconfig>/eval/insert.php";

int irPin = 23;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(irPin, INPUT);
}

void loop() {
  int val = digitalRead(irPin);
  Serial.print("IR Sensor Reading: ");
  Serial.println(val);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?value=" + String(val);
    http.begin(url);
    int httpCode = http.GET();

    Serial.print("Sent to server -> ");
    Serial.print(url);
    Serial.print(" | HTTP Response: ");
    Serial.println(httpCode);

    http.end();
  } else {
    Serial.println("WiFi Disconnected!");
  }

  delay(2000);
}
