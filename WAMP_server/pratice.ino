#include <WiFi.h>
#include <HTTPClient.h>

// ====== WiFi Credentials ======
const char* ssid     = "Your_SSID";
const char* password = "Your_PASSWORD";

// ====== Server Configuration ======
const char* serverURL = "http://<IPv4_Address>/test/insert.php";  // your PC's WAMP IPv4

// ====== Pin Configuration ======
const int irObjectPin = 16;   // Object detection sensor
const int irFloorPin  = 17;   // Floor detection sensor
const int ledPin      = 4;    // LED control pin

// ====== Function Prototypes ======
void sendReading(String sensor, int val);
void checkLEDState();

void setup() {
  Serial.begin(115200);
  pinMode(irObjectPin, INPUT);
  pinMode(irFloorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read both IR sensors
    int objectVal = digitalRead(irObjectPin);
    int floorVal  = digitalRead(irFloorPin);

    // Send readings
    sendReading("object_detection", objectVal);
    delay(500);
    sendReading("floor_detection", floorVal);
    delay(500);

    // Check LED state from server
    checkLEDState();
  } else {
    Serial.println("⚠️ WiFi disconnected, reconnecting...");
    WiFi.reconnect();
  }

  delay(2000);
}

// ====== Function: Send IR Sensor Data ======
void sendReading(String sensor, int val) {
  HTTPClient http;
  String url = String(serverURL) + "?sensor=" + sensor + "&value=" + String(val);
  http.begin(url);
  int code = http.GET();

  Serial.printf("Sent [%s]: %s -> HTTP %d\n", sensor.c_str(), val ? "DETECTED" : "CLEAR", code);
  http.end();
}

// ====== Function: Check LED State ======
void checkLEDState() {
  HTTPClient http;
  String url = String(serverURL) + "?led_check=1";
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();

    // Expect "0" or "1" only
    if (payload.indexOf("1") != -1) {
      digitalWrite(ledPin, HIGH);
      Serial.println("💡 LED ON");
    } else {
      digitalWrite(ledPin, LOW);
      Serial.println("💡 LED OFF");
    }
  } else {
    Serial.println("⚠️ Failed to check LED state");
  }

  http.end();
}
