/*
https://wokwi.com/projects/388367944197425153
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels
const int scale_GAIN = 128; //Folgende Verstärkungen sind möglich: 32, 64, 128
const float scale_ANZ_MESSWERTE = 1; //Anzahl der Messwerte (wirkt als gleitender Mittelwert / Hochpass)
const float scale_FAKTOR = 420; //Skalierung ADC Wert zu Kraft (ADC Wert / Kraft)

// create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
HX711 scale;

void setup() {
  Serial.begin(9600);

    Serial.println(F("Start"));
  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
    scale.begin(0, 1);
    scale.set_gain(scale_GAIN); //Verstärkung
    scale.set_scale(scale_FAKTOR); //Skalierung (konvertiert ADC Wert in Newton)
  

  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 10);       // set position to display
  oled.println("JanWarHier"); // set text
  oled.display();              // display on OLED
}
float MaxValue = 0.0;
bool debug = false;
void loop() {  
  
  oled.clearDisplay(); // clear display
  float value = scale.get_units();
  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 1);       // set position to display
  if(debug)
  {
    oled.print(value,3); // set text
    oled.println("Kg"); // set text
  }

  if(value<MaxValue)
  {
    oled.setTextSize(2);         // set text size
    float p = value/MaxValue *10;
      for(int i = 0; i < p ; i++)
      {
        oled.print("#"); // set text
      }
      oled.println();
     
      p = p*10;
      if(p>10){
        oled.setTextSize(1);         // set text size
        oled.print(p);
        oled.println("%");
      }
      else
      {
        oled.setTextSize(2);         // set text size
        oled.println("PLZ make\n new Coffe");
      }
  }
  else if(value>MaxValue)
  {
        oled.setTextSize(2);         // set text size
        oled.println("Mhhh new\n Coffe");
  }
  else
  {    
    if(MaxValue > 0.0){
      if(debug)
      {
        oled.print("MaxValue: "); // set text
        oled.print(MaxValue,3); // set text
        oled.println("Kg"); // set text
      }
        oled.println("Full lets go"); // set text
    }else{
        oled.print(value,3); // set text
        oled.println("Kg"); // set text
        oled.println("NoMaxValueSet\nPressButton");
    }
  }
  oled.display();   
  delay(500); 
  if (digitalRead(5) == HIGH) {
        Serial.println("Button Pressed");
        MaxValue = scale.get_units();
      }else{
        
        Serial.println("Button Not Pressed");
      }
}
