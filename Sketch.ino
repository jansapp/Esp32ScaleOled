/*
https://wokwi.com/projects/388281502876573697
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 32 // OLED height, in pixels
const int GAIN = 128; //Folgende Verstärkungen sind möglich: 32, 64, 128
const float MESSWERTE = 1; //Anzahl der Messwerte (wirkt als gleitender Mittelwert / Hochpass)
const float FAKTOR = 420; //Skalierung ADC Wert zu Kraft (ADC Wert / Kraft)

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
HX711 scale;

void setup() {
  Serial.begin(9600);

  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
  scale.begin(0, 1);
  scale.set_gain(GAIN); //Verstärkung
  scale.set_scale(FAKTOR); //Skalierung (konvertiert ADC Wert in Newton)

  delay(2000);
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("JanWarHier");
  oled.display();            
  Serial.println(F("SetupDone"));
}

void loop() {  
  
  delay(2000);
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);        
  oled.setTextColor(WHITE);   
  oled.setCursor(0, 10);      
  Serial.print(scale.get_units(),5);
  Serial.println(" Kg");
  oled.print(scale.get_units(),5);
  oled.println("Kg");
  oled.display();   
}
