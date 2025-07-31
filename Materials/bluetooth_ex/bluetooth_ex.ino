#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
const int ledPin = 2; // Change this if you’re using a different pin

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32LED"); // Name shown in Bluetooth list
  pinMode(ledPin, OUTPUT);
  Serial.println("Bluetooth device is ready to pair");
}
void loop() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
    if (receivedChar == '1') {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED ON");
    } else if (receivedChar == '0') {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED OFF");
    }
  }
}
