#include "Ultrasonic.h"
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SH1106.h" 
SH1106  display(0x3c, D1, D2);
// replace with your channel's thingspeak API key, 
String apiKey = "Your API Key";
const char* ssid = "Your WiFi";
const char* password = "Your Password";
 
const char* server = "api.thingspeak.com";

Ultrasonic ultrasonic(13);
WiFiClient client;
   
 
void setup() {     
  Serial.begin(115200);
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
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  delay(150);
  display.clear(); 

  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(RangeInCentimeters);
           /*
           postStr +="&field2=";
           postStr += String(h);
           postStr += "\r\n\r\n";*/
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     Serial.print("Distance: ");
     Serial.print(RangeInCentimeters);
     display.drawString(0, 0,"Ultrasonic sensor");
     display.drawString(0, 20,"Distance: ");
     display.drawString(0, 30,String(RangeInCentimeters));
     display.drawString(10, 30,"cm");
     Serial.println("cm send to Thingspeak");
     display.drawString(0, 10, "Send to Thingspeak");   
     display.display(); 
  }
  client.stop();
   
  Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  
  for(unsigned int i = 0; i < 10; i++)
  {
    delay(1000);                         
  }
}
