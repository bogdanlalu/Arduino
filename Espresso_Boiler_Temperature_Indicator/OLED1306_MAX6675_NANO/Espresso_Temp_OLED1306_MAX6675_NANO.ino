#include <SPI.h>
#include <Wire.h>  // for I2C protocol

#include <Adafruit_Sensor.h> // for 128x64 I2C OLED screen
#include <Adafruit_SSD1306.h> // for 128x64 I2C OLED screen
#include <max6675.h> // for thermocouple

// Define OLED Properties
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define thermo_pin_SO 4 //SO
#define thermo_pin_CS 5 //CS
#define thermo_pin_CLK 6 //SCK

// Instantiate thermocouple object as 'thermocouple' connected to SPI pins(CLK, CS, SO)
MAX6675 thermocouple(thermo_pin_CLK, thermo_pin_CS, thermo_pin_SO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay(); 
}
void loop() {
  display.clearDisplay();
  float t = thermocouple.readCelsius();

  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(10, 18);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  
  if (isnan(t)) {
    display.println("NO TEMP");
    display.display();
  }
  else{
    display.println(t);
    display.display();
  }
  
  delay(1000);
}
