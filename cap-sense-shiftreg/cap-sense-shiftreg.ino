#include <FastLED.h>
#define NUM_LEDS 2
CRGB leds[NUM_LEDS];

void setup() { 
  Serial.begin(115200); 
  FastLED.addLeds<WS2811, 6>(leds, NUM_LEDS); 
  // pinMode(A3, INPUT); 
}

void loop() {
  // Serial.println("black"); 
  // leds[0] = CRGB::Black; leds[1] = CRGB::Black; FastLED.show(); 
  // delay(10000); 
  // Serial.println("white"); 
  
  // leds[0] = CRGB::White; leds[1] = CRGB::White; FastLED.show(); 
  // delay(10000); 

  // leds[0] = CRGB::Black; leds[1] = CRGB::Black; FastLED.show(); delay(1000);
  // leds[0] = CRGB::Black; FastLED.show(); delay(500);
  doRead(); 
  
  delay(10);
}

void doRead() {
  delay(10); 
  leds[0] = CRGB::White; leds[1] = CRGB::Black; FastLED.show(); 
  delay(10); 
  Serial.print("SENSOR 1: "); 
  Serial.print(analogRead(A3)); 
  
  delay(10);
  leds[0] = CRGB::Black; leds[1] = CRGB::White; FastLED.show(); 
  delay(10); 
  Serial.print(", Sensor 2: "); 
  Serial.println(analogRead(A3)); 

}