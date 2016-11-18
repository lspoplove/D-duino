![image](https://github.com/lspoplove/D-duino/blob/master/Documents/D-duino-B.jpg)


All this tutorial is under D-duino-B platform
https://www.tindie.com/products/lspoplove/d-duino-barduino-and-nodemcu-and-esp8266-and-13oled

If you want to use D-duino,
Please change #include "SH1106.h"  ->  #include "SSD1306.h" 
       change SH1106  display(0x3c, D1, D2) -> SSD1306  display(0x3c, D1, D2)

D-duino has 0.96 OLED which is using SSD1306
D-duino-B has 1.3 OLED which is using SH1106

Project:
Control Grove LED by Web
http://www.instructables.com/id/Control-Grove-LED-by-WebD-duino-B/

Display distance by Ultrasonic sensor and Upload to ThingSpeak
http://www.instructables.com/id/Display-Distance-by-Ultrasonic-Sensor-and-Upload-t/
