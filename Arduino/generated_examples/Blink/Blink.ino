#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 11
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

int intervali[NUM_LEDS] = {500, 500, 500, 500, 500, 500, 500, 500};
unsigned long timer[NUM_LEDS];

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    unsigned long cas = millis();
    for (int i = 0; i < NUM_LEDS; i++) {
      timer[i] = cas;
    }
}

void loop() { 
  //leds[0] = CRGB::Red;
  //FastLED.show();
  for (int i = 0; i < NUM_LEDS; i++) {
    //preverimo, ali je zadnja sprememba ledice starejša od intervala
    if(timer[i] + 500 < cas){
      if(leds[i] == CRGB::Black){
        leds[i] = CRGB::White;
    }
    else{
      leds[i] = CRGB::Black;
    }

    timer[i] = cas;
    }
  }
  FastLED.show();
}
