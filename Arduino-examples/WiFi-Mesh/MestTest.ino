#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>
#include "SSD1306.h"
unsigned int request_i = 0;
unsigned int response_i = 0;

String manageRequest(String request);
SSD1306  display(0x3c, D1, D2);
/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);

/**
 * Callback for when other nodes send you data
 *
 * @request The string received from another node in the mesh
 * @returns The string to send back to the other node
 */
String manageRequest(String request)
{
	/* Print out received message */
	Serial.print("received: ");
	Serial.println(request);

	/* return a string to send back */
	char response[60];
	sprintf(response, "Hello world response #%d from Mesh_Node%d.", response_i++, ESP.getChipId());
	return response;
}

void setup()
{
	Serial.begin(115200);
	delay(10);
	Serial.println();
	Serial.println();
  Serial.println("Setting up mesh node...");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "WiFi  Mesh Test");
  display.drawString(0, 10, "Chip ID is");
  display.drawString(60, 10, (String)(ESP.getChipId()));
	/* Initialise the mesh node */
	mesh_node.begin();
}

void loop()
{
	/* Accept any incoming connections */
	mesh_node.acceptRequest();
  display.display();
	/* Scan for other nodes and send them a message */
	char request[60];
	sprintf(request, "Hello world request #%d from Mesh_Node%d.", request_i++, ESP.getChipId());
	mesh_node.attemptScan(request);
	delay(1000);
}
