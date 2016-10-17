/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SSD1306.h" 
SSD1306  display(0x3c, D1, D2);
void setup() {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  display.clear(); 
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found"); 
    display.drawString(0, 0,"no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    display.drawString(0, 0,String(n));
    display.drawString(10, 0,"networks found");
    int k =0;
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found     
      display.drawString(0,10+k,String(WiFi.SSID(i))); 
      display.drawString(80,10+k,String(WiFi.RSSI(i))); 
      display.drawString(100,10+k,"db"); 
      k=k+10;
      delay(10);
    }
    display.display();
  }
  // Wait a bit before scanning again
  delay(5000);
}
