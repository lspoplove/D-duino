/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "SSD1306.h" 
SSD1306  display(0x3c, D1, D2);
WiFiClient client;
String data = "";
String tempIP = "";
const char *ssid = "BWSAG";
const char *password = "bshg@rfda";

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
 // display.drawString(0, 20, data);

  if(data.length()<21){
  display.drawString(0, 20, data);
  }
  else if(21<data.length()<41){
  display.drawString(0, 20, data.substring(0,21));
  display.drawString(0, 30, data.substring(21,data.length()));
  }
  else if(42<data.length()<63){
  display.drawString(0, 20, data.substring(0,21));
  display.drawString(0, 30, data.substring(21,42));
  display.drawString(0, 40, data.substring(42,data.length()));
  }
  else if(63<data.length()<84){
  display.drawString(0, 20, data.substring(0,21));
  display.drawString(0, 30, data.substring(21,42));
  display.drawString(0, 40, data.substring(42,63));
  display.drawString(0, 50, data.substring(63,data.length()));
  }
 
display.display(); 
}
