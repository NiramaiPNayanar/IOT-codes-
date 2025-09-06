#include <WiFi.h>
//#include <WebSocketsServer.h>
#include <WebSocketsServer_Generic.h>

const char* ssid = "karthi";
const char* password = "karthiamrita123";

WebSocketsServer webSocket = WebSocketsServer(81);

#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
 //S Serial.println(WiFi.localIP());
  webSocket.begin();
  Serial.println(WiFi.localIP());
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String message = (char*) payload;
    if (message == "ON") {
      digitalWrite(LED_PIN, HIGH);
    } else if (message == "OFF") {
      digitalWrite(LED_PIN, LOW);
    }
  }
}