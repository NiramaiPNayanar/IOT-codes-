#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "RevSinMax";
const char* password = "alrightokay2";
const char* mqtt_server = "172.20.10.5";

WiFiClient espClient;
PubSubClient client(espClient);

const int lm35Pin = 34; // analog pin for ESP32

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void reconnect() {
  while (!client.connected()) client.connect("LM35_Client");
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int adcValue = analogRead(lm35Pin);
  float voltage = adcValue * (3.3 / 4095.0);
  float temperature = voltage * 100.0; // 10mV/°C

  char msg[10];
  dtostrf(temperature, 4, 2, msg);
  client.publish("sensor/temperature", msg);

  Serial.print("Temperature: ");
  Serial.println(temperature);

  delay(2000);
}
