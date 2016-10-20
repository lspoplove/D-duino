
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, D1, D2);
WiFiClient client;
String data = "";
String tempIP = "";
const char *ssid = "Your WiFi";
const char *password = "Your Password";

ESP8266WebServer server ( 80 );

String form =
  "<html>"
  "<p>"
  "<center>"
  "<h1>Talk to D-duino</h1>"
  "<form action='msg'><p>Type your message <input type='text' name='msg' size=100 autofocus> <input type='submit' value='Submit'></form>"
  "</center>"
  "</html>" ;

void handleRoot() {
	server.send ( 200, "text/html", form);
  String msg = server.arg("msg");
  Serial.println(msg);
  data = msg;
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

void setup ( void ) {
	Serial.begin ( 115200 );
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  delay(10);
	WiFi.begin ( ssid, password );
	Serial.println ( "" );
	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	Serial.println ( "" );
	Serial.print ( "Connected to " );
	Serial.println ( ssid );
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );
  tempIP =WiFi.localIP().toString(); 
	if ( MDNS.begin ( "esp8266" ) ) {
		Serial.println ( "MDNS responder started" );
	}
  server.on("/", []() {
  server.send(200, "text/html", form);
  });
	server.on ( "/msg", handleRoot );
	server.on ( "/inline", []() {
	server.send ( 200, "text/plain", "this works as well" );
	} );
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );
  
}

void loop ( void ) {
  display.clear();
	server.handleClient();
  display.drawString(0, 0,"WiFi connected"); 
  display.drawString(0, 10,tempIP); 
  display.drawString(0, 20, data);   
  display.display(); 
}
