#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DHT11.h>

DHT11 dht11(6);
 
const char* ssid = "DOM";
const char* password = "amszczecin";
MDNSResponder mdns;
ESP8266WebServer server(80);
int distance = 0;


String webPage = "";



void handleRoot() {
  server.send(200, "text/plain", webPage);
}

 
void setup(void){
  float humi, temp = 0;
 dht11.read(humi, temp); 
webPage = "<div style=\"width: 500px; margin: auto; border: 1px solid black; text-align: center;\">";
webPage += "<h1 style=\"margin: auto\">Kontrola Robota VKE-01</h1>";
webPage += "<h3 style=\"margin: auto 0\">#1:";
webPage += analogRead((1)*5/1023*100)/5 + "%</h3>";
webPage += "<h3 style=\"margin: auto 0\">#2:";
webPage += analogRead((2)*5/1023*100)/5 + "%";
webPage += "<h3 style=\"margin: auto 0\">#TEMP:";
webPage += (String)temp +"&#186C; </h3> ";
webPage += "<br / >";
webPage += "<p><a href=\"up\"><button style=\"width: 50px\">^</button></a></p>";
webPage += "<p>";
webPage += "<a href=\"left\"><button><</button></a>";
webPage += "<a href=\"beep\"><button style=\"width: 50px\"> ! </button></a>";
webPage += "<a href=\"right\"><button>></button></a>";
webPage += "</p>";
webPage += "<p><a href=\"down\"><button  style=\"width: 50px\">v</button></a></p>";
webPage += "<br >";
webPage += "<br />";
webPage += "<br />";
webPage += "<p align=\"right\">by Rafał Rożek</p>";
webPage += "<p align=\"right\">dla <a href="">http://www.informatyka.am.szczecin.pl/</a></p>";
webPage += "</div>";
  
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  
  server.on("/up", [](){
  handleRoot();
  digitalWrite(15,HIGH);
  delay(100);
  digitalWrite(15,LOW);
  distance++;
  });
  
  server.on("/down", [](){
  handleRoot();
  digitalWrite(14,HIGH);
  delay(100);
  digitalWrite(14,LOW);
  distance++;
  });
  server.on("/left", [](){
  handleRoot();
    digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  });
  server.on("/right", [](){
  handleRoot();
  
  digitalWrite(12,HIGH);
  delay(100);
  digitalWrite(12,LOW);
  });
  server.on("/beep", [](){
  handleRoot();
    digitalWrite(11,HIGH);
  delay(100);
  digitalWrite(11,LOW);
  });

  server.onNotFound(handleRoot);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
}
