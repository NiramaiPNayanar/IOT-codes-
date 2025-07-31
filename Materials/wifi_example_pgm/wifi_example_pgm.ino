#include <WiFi.h>
#include <WebServer.h> 

const char *ssid="JioFiber-etmU9";
//"iPhone";
const char *password="rameshkarthi123"; //"karthiamrita";
IPAddress local_ip(192,168,29,233);
IPAddress gateway(192,168,29,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

String page = "";


uint8_t LEDPin1 = 2;
bool LED1status = LOW;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(LEDPin1,OUTPUT);

WiFi.softAP(ssid, password);
WiFi.softAPConfig(local_ip, gateway, subnet);
Serial.println(" ip address");
Serial.println(WiFi.softAPIP());

delay(100);

server.on("/",handle_onConnect);
server.on("/led1on",handle_led1on);
server.on("/led1off",handle_led1off);
server.onNotFound(handle_NotFound);

server.begin();
Serial.println(" Http Server Started");
}

void loop() {
  // put your main code here, to run repeatedly:

  server.handleClient();
  if(LED1status)
    digitalWrite(LEDPin1,HIGH);
  else
  digitalWrite(LEDPin1,LOW);
  handle_onConnect();

}
void handle_onConnect()
{
  LED1status = LOW;
  Serial.println(" Gpio pin Off");

  //server.send(200,"text\html", sendHTML(LED1status));

  server.on("/", [](){
    page = "<h1>Sensor to ESP Web Server</h1><h3>Data:</h3> <h4>"+String(LED1status)+"</h4>";
    server.send(200, "text/html", page);
  });
} 

void handle_led1on()
{
  LED1status = HIGH;
  Serial.println(" Gpio pin on");
  
  server.on("/", [](){
    page = "<h1>Sensor to ESP Web Server</h1><h3>Data:</h3> <h4>"+String(LED1status)+"</h4>";
    server.send(200, "text/html", page);
  });
  
  //server.send(200,"text\html", sendHTML(true,LED1status));

} 

void handle_led1off()
{
  LED1status = LOW;
  Serial.println(" Gpio pin OFF");
 server.on("/", [](){
    page = "<h1>Sensor to ESP Web Server</h1><h3>Data:</h3> <h4>"+String(LED1status)+"</h4>";
    server.send(200, "text/html", page);
  });
 
 
 // server.send(200,"text\html", sendHTML(false,LED1status));
}

void handle_NotFound()
{
  Serial.println(" Gpio pin OFF");
  server.send(404,"text\html", "not Found");
} 
