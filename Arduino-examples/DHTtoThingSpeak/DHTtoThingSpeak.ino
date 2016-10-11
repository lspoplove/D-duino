#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SSD1306.h" 
SSD1306  display(0x3c, D1, D2);
// replace with your channel's thingspeak API key, 
String apiKey = "Your API Key";
const char* ssid = "Your WiFi";
const char* password = "Your password";
 
const char* server = "api.thingspeak.com";
#define DHTPIN 2 // what pin we're connected to
 
DHT dht(DHTPIN, DHT11,15);
WiFiClient client;
   
 
void setup() {     
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  delay(10);
  dht.begin();
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
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(t);
           postStr +="&field2=";
           postStr += String(h);
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
           
 
     Serial.print("Temperature: ");
     Serial.print(t);
     display.drawString(0, 20,"Temperature: ");
     display.drawString(0, 30,String(t));
     Serial.print(" degrees Celcius Humidity: "); 
     Serial.print(h);
     display.drawString(0, 40,"Humidity: ");
     display.drawString(0, 50,String(h));
     display.drawString(30, 50,"%");
     Serial.println("% send to Thingspeak");
     display.drawString(0, 10, "Send to Thingspeak");   
     display.display(); 
  }
  client.stop();
   
  Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  for(unsigned int i = 0; i < 20; i++)
  {
    delay(3000);                         
  }
}
