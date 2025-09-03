#include <WiFi.h>

const char* ssid = "karthi";         // Replace with your WiFi name
const char* password = "karthiamrita123"; // Replace with your WiFi password

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);           // Start connecting to WiFi

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());       // Print ESP32 local IP
}

void loop() {
  // Nothing needed here
}
