#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "SH1106.h" //if you use d-duino please change to SSD1306
SH1106  display(0x3c, D1, D2);//if you use d-duino please change to SSD1306
WiFiClient client;
String data = "";
String tempIP = "";

const char* ssid = "Your WiFi";
const char* password = "Your password";

ESP8266WebServer server(80);
 
const int led = 0;

String form =
  "<html>"
  "<p>"
  "<center>"
  "<h1>Talk to D-duino</h1>"
  "<form action='msg'><p>Type your message <input type='text' name='msg' size=100 autofocus> <input type='submit' value='Submit'></form>"
  "<p>"
  "</center>"
  "</html>" ;
  
void handleRoot() {
  server.send(200, "text/html",form);
  String msg = server.arg("msg");
  Serial.println(msg);
  data = msg;
  if(msg=="open")
  {
    digitalWrite(led, 1);
  }else if(msg=="off")
  {
    digitalWrite(led, 0);
  }
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
   display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  delay(10);
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
  tempIP =WiFi.localIP().toString();
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

   server.on("/", []() {
  server.send(200, "text/html", form);
});
  server.on ( "/msg", handleRoot );
  server.on("/inline", [](){
   server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop ( void ) {
  display.clear();
  server.handleClient();
  display.drawString(0, 0,tempIP); 
  display.drawString(0, 10, "WiFi connected");

  if(data.length()<21){
  display.drawString(0, 20, data);
  }
  else if(data.length()>21&&data.length()<41){
  display.drawString(0, 20, data.substring(0,21));
  display.drawString(0, 30, data.substring(22,data.length()));
  }
  else if(data.length()>42&&data.length()<63){
  display.drawString(0, 20, data.substring(0,21));
  display.drawString(0, 30, data.substring(22,43));
  display.drawString(0, 40, data.substring(44,data.length()));
  }
  else if(data.length()>63&&data.length()<84){
  display.drawString(0, 20, data.substring(0,21));
  display.drawString(0, 30, data.substring(22,43));
  display.drawString(0, 40, data.substring(44,65));
  display.drawString(0, 50, data.substring(66,data.length()));
  }
  else
  {
    display.drawString(0, 20, "Please input shortly");
  }
  
 
display.display(); 
}
