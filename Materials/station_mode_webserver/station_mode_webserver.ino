#include <WiFi.h>

const char* ssid = "karthi";
const char* password = "karthiamrita123";
WiFiServer server(80);

const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("/ON") != -1) {
      digitalWrite(ledPin, HIGH);
    } else if (request.indexOf("/OFF") != -1) {
      digitalWrite(ledPin, LOW);
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<html><body><h1>ESP32 LED Control</h1>");
    client.println("<a href=\"/ON\">Turn ON</a><br>");
    client.println("<a href=\"/OFF\">Turn OFF</a>");
    client.println("</body></html>");
    client.stop();
  }
}
