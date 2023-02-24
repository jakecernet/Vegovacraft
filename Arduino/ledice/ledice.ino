#include <FastLED.h>
#define NUM_LEDS 9
#define DATA_PIN 11
#define CLOCK_PIN 11

CRGB leds[NUM_LEDS];

const int rs = 12, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(A0, ENABLE_LED_FEEDBACK);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  lcd.begin(16, 2);
  lcd.print("Hello, world!");
}

void loop() {
  
}
