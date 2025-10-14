#include <WiFi.h>
const char* ssid = "ESP32_LED";      // Wi-Fi SSID
const char* password = "12345678";   // Wi-Fi Password
// esp32 wifi network is created  
WiFiServer server(80);		// wifi server is created with object name server
const int ledPin = 2;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  // Start Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP Started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();					// starts the server
}
void loop() {
WiFiClient client = server.available();	// check if server has any clients request 
  if (client) {
          Serial.println("New Client Connected");
          String request = client.readStringUntil('\r');

//  "GET /ON HTTP/1.1"  is the msg sent from client to server 

          Serial.println("Request: " + request);
          client.flush();
              // Control LED
              if (request.indexOf("/ON") != -1) {
                digitalWrite(ledPin, HIGH);
              } else if (request.indexOf("/OFF") != -1) {
                digitalWrite(ledPin, LOW);
              }
          // Send HTML response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>ESP32 LED Control</title></head>");
          client.println("<body><h1>LED Control</h1>");
          client.println("<p><a href=\"/ON\"><button>ON</button></a></p>");
          client.println("<p><a href=\"/OFF\"><button>OFF</button></a></p>");
          client.println("</body></html>");
          delay(1);
          client.stop();
          Serial.println("Client Disconnected");
  }
}
