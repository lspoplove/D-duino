#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "SH1106.h" 
// NeoPixel stick DIN pin
#define DIN_PIN D3
SH1106  display(0x3c, D1, D2);
// How many NeoPixels on the stick?
#define NUM_PIXELS 12

WiFiClient client;
String data = "";
String tempIP = "";

const char* ssid = "xxxx";
const char* password = "xxxx";

ESP8266WebServer server(80);

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
    if(msg=="red")
  {
    colorRed();
  }else if(msg=="green")
  {
   colorGreen();
  }else if(msg=="blue")
  {
   colorBlue();
  }else if(msg=="white")
  {
   colorWhite();
  } else if(msg=="cyan")
  {
   colorCyan();
  } else if(msg=="magenta")
  {
   colorMagenta();
  }else if(msg=="yellow")
  {
   colorYellow();
  }else if(msg=="black")
  {
   colorBlack();
  }else if(msg=="chasered")
  {
   colorChaseRed();
  }else if(msg=="chasegreen")
  {
   colorChaseGreen();
  }else if(msg=="chaseblue")
  {
   colorChaseBlue();
  }else if(msg=="chasewhite")
  {
   colorChaseWhite();
  }else if(msg=="random")
  {
   colorRandom();
  }else if(msg=="rainbow")
  {
   colorRainbow();
  }else if(msg=="rainbowcycle")
  {
   colorRainbowCycle();
  }else if(msg=="chaserainbow")
  {
   colorChaseRainbow();
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


// Third parameter:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream (NeoPixel Stick)
//   NEO_KHZ400  400 KHz bitstream for FLORA pixels
//   NEO_KHZ800  800 KHz bitstream for High Density LED strip (NeoPixel Stick)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, DIN_PIN, NEO_GRB + NEO_KHZ800);

int pause = 1000;

void setup() {
  Serial.begin(9600);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  delay(10);
  WiFi.begin(ssid, password);
  Serial.println("");
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
  strip.begin();
  strip.show(); // Start with all pixels off
  delay(pause);
}

void loop() {
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

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  uint16_t i;
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void randomColors(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<50; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(random(0,255), random(0,255), random(0,255)));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  uint16_t j, q, i;
  for (j=0; j<10; j++) {  //do 10 cycles of chasing
    for (q=0; q < 3; q++) {
      for (i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  uint16_t j, q, i;
  for (j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (q=0; q < 3; q++) {
      for (i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void colorRed()
{
    Serial.println("Color Wipe Red");
  colorWipe(strip.Color(255, 0, 0), 50);
  delay(pause);
}
void colorGreen()
{
  Serial.println("Color Wipe Green");
  colorWipe(strip.Color(0, 255, 0), 50);
  delay(pause);
}
void colorBlue()
{
  Serial.println("Color Wipe Blue");
  colorWipe(strip.Color(0, 0, 255), 50);
  delay(pause);
}
void colorWhite()
{
  Serial.println("Color Wipe White");
  colorWipe(strip.Color(255, 255, 255), 50);
  delay(pause);
}
void colorCyan()
{
  Serial.println("Color Wipe Cyan");
  colorWipe(strip.Color(0, 255, 255), 50);
  delay(pause);
}
void colorMagenta()
{
 Serial.println("Color Wipe Magenta");
  colorWipe(strip.Color(255, 0, 255), 50);
  delay(pause);
}
void colorYellow()
{
 Serial.println("Color Wipe Yellow");
  colorWipe(strip.Color(255, 255, 0), 50);
  delay(pause);
}
void colorBlack()
{
  Serial.println("Color Wipe Black");
  colorWipe(strip.Color(0, 0, 0), 50);
  delay(pause);
}
void colorChaseRed()
{
 Serial.println("Theater Chase Red");
  theaterChase(strip.Color(127, 0, 0), 50);
  delay(pause);
}
void colorChaseGreen()
{
  Serial.println("Theater Chase Green");
  theaterChase(strip.Color(0, 127, 0), 50);
  delay(pause);
}
void colorChaseBlue()
{
  Serial.println("Theater Chase Blue");
  theaterChase(strip.Color(0, 0, 127), 50);
  delay(pause);
}
void colorChaseWhite()
{
  Serial.println("Theater Chase White");
  theaterChase(strip.Color(127, 127, 127), 50);
  delay(pause);
}
void colorRandom()
{
  Serial.println("Random Colors");
  randomColors(100);
  delay(pause);
}
void colorRainbow()
{
  Serial.println("Rainbow");
  rainbow(20);
  delay(pause);
}
void colorRainbowCycle()
{
 Serial.println("Rainbow Cycle");
  rainbowCycle(20);
  delay(pause);
}
void colorChaseRainbow()
{
  Serial.println("Theater Chase Rainbow");
  theaterChaseRainbow(50);
  delay(pause);
}
