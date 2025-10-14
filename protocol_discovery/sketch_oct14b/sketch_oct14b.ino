#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFiUdp.h>

const char* ssid     = "RevSinMax";
const char* password = "alrightokay2";

// HTTP server (port 8080)
WebServer httpServer(8080);

// Raw TCP server (port 9090)
WiFiServer tcpServer(9090);

// UDP server (port 4210)
WiFiUDP udp;
unsigned int udpPort = 4210;
char incomingPacket[255];

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // mDNS responder as "revsin.local"
  if (!MDNS.begin("revsin")) {
    Serial.println("Error setting up mDNS responder!");
    while (1) { delay(1000); }
  }
  Serial.println("mDNS responder started: http://revsin.local/");

  // Advertise services
  MDNS.addService("http", "tcp", 8080);
  MDNS.addService("tcpraw", "tcp", 9090);
  MDNS.addService("udp", "udp", 4210);

  // Setup HTTP routes
  httpServer.on("/", []() {
    httpServer.send(200, "text/plain", "Hello from ESP32 HTTP server on port 8080!");
  });
  httpServer.on("/status", []() {
    httpServer.send(200, "application/json", "{\"status\":\"ok\",\"port\":8080}");
  });
  httpServer.begin();
  Serial.println("HTTP server started on port 8080");

  // Start TCP server
  tcpServer.begin();
  Serial.println("Raw TCP server started on port 9090");

  // Start UDP listener
  udp.begin(udpPort);
  Serial.printf("UDP server listening on port %d\n", udpPort);
}

void loop() {
  // Handle HTTP clients
  httpServer.handleClient();

  // Handle TCP clients
  WiFiClient client = tcpServer.available();
  if (client) {
    Serial.println("New TCP client connected (9090)");
    client.println("Welcome to ESP32 TCP Echo server (type something)");
    
    while (client.connected()) {
      while (client.available()) {
        String msg = client.readStringUntil('\n');  // read line
        msg.trim();
        if (msg.length() > 0) {
          Serial.printf("TCP Received: %s\n", msg.c_str());
          client.print("Echo: ");
          client.println(msg);
        }
      }
      delay(10);
    }
    Serial.println("TCP client disconnected");
    client.stop();
  }

  // Handle UDP packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = 0;

    Serial.printf("UDP packet from %s:%d\n",
                  udp.remoteIP().toString().c_str(),
                  udp.remotePort());
    Serial.printf("Contents: %s\n", incomingPacket);

    // Reply back with echo
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.print("Echo: ");
    udp.print(incomingPacket);
    udp.endPacket();
  }
}

// ipaddr - ip of board
// to test http - ipaddr:8080 on browser
// to check http status - ipaddr:8080/status on browser
// to test tcp - putty ip - ipaddr, port - 9090, connection type - raw
// to test udp - nmap -sU -p 4210 172.20.10.2
