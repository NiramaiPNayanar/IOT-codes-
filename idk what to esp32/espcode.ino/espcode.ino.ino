#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Hotspot";
const char* password = "123456789";

WebServer server(80);
const int ledPin = 4;

String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>LED Control</title></head>
<body>
<h2>ESP32 HTTP LED Control</h2>
<button onclick="fetch('/toggle')">Toggle LED</button>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleToggle() {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.send(200, "text/plain", "Toggled");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
}