/* *********************************************************************************
 * ESP8266 QRcode
 * dependency library :
 *   ESP8266 Oled Driver for SSD1306 display by Daniel Eichborn, Fabrice Weinberg
 *
 * SDA --> D1
 * SCL --> D2
***********************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <qrcode.h>
#include <SSD1306.h>

const char *ssid = "BWSAG";
const char *password = "bshg@rfda";

SSD1306  display(0x3c,D1,D2);
QRcode qrcode (&display);
String content = "www.dong-sen.com";
ESP8266WebServer server ( 80 );

void handleRoot() {
   char temp[400];
   snprintf ( temp, 400,
   "<html>\
       <head>\
    <meta http-equiv='refresh' content='1'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
  
  </body>\
</html>");
  server.send(200, "text/html",temp);
}

void handleNotFound() {
 String message = "File Not Found\n\n";
 message += "URI: ";
 message += server.uri();
 message += "\nMethod: ";
 message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
 message += "\nArguments: ";
 message += server.args();
 message += "\n";

 for ( uint8_t i = 0; i < server.args(); i++ ) {
  message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
 }

 server.send ( 404, "text/plain", message );
}

void setup() {
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting...");
    WiFi.begin ( ssid, password );
    Serial.println ( "" );
    display.init();
    display.clear();
    display.display();
    qrcode.init();

   while ( WiFi.status() != WL_CONNECTED ) {
  delay ( 500 );
  Serial.print ( "." );
 }
Serial.println ( "" );
 Serial.print ( "Connected to " );
 Serial.println ( ssid );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 if ( MDNS.begin ( "esp8266" ) ) {
  Serial.println ( "MDNS responder started" );
}
 server.on ( "/", handleRoot );
 server.on ( "/inline", []() {
  server.send ( 200, "text/plain", "this works as well" );
 } );
 server.onNotFound ( handleNotFound );
 server.begin();
 Serial.println ( "HTTP server started" );
}

void loop() {
  qrcode.create(content);
  delay(500);
  server.handleClient();
  }
