#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SSD1306.h" 
SSD1306  display(0x3c, D1, D2);
// replace with your channel's thingspeak API key, 
String apiKey = "API key";
const char* ssid = "Your WiFi SSID";
const char* password = "Your WiFi password";
 
const char* server = "api.thingspeak.com";
 
WiFiClient client;
void setup() {     
  Serial.begin(115200);
  pinMode(A0,INPUT);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  delay(10);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
}
 
 
void loop() {
  display.clear(); 
  int temp = analogRead(A0);
 
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(temp);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     Serial.print("Moisture Sensor Value: ");
     Serial.print(temp);
     display.drawString(0, 20,"Moisture: ");
     display.drawString(0, 30,String(temp));
     Serial.println(" send to Thingspeak");
     display.drawString(0, 10, "Send to Thingspeak");   
     display.display(); 
  }
  client.stop();
   

   Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  // Here I set upload every 60 seconds
  for(unsigned int i = 0; i < 20; i++)
  {
    delay(3000);                         
  }                       
}
