This is an example of how to use the D-Duino whit the Adafruit_SSD1306 and Adafruit_GFX libraries. 

Based on: https://github.com/adafruit/Adafruit_SSD1306

The D-duino Esp8266 does not use the default SDA / SCL pins for the OLED display. The Adafruit_GFX.h library then tries to send output to the wrong pins.

The fix is simple

Define the pins to be used:

	#define OLED_RESET D0  // RST-PIN for OLED (not used)
	#define OLED_SDA    D1  // SDA-PIN for I2C OLED
	#define OLED_SCL    D2  // SCL-PIN for I2C OLED
	Adafruit_SSD1306 display(OLED_RESET);

In setup() add this to use it: (aka the magic)

  // initial I2C bus and OLED display
  Wire.begin(OLED_SDA, OLED_SCL);
  Wire.setClock(400000);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
