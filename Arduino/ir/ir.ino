#include <IRremote.hpp>
#include <FastLED.h>
#include <LiquidCrystal.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#define DECODE_NEC
#define IZPISI_TIPKO(x) Serial.println(#x);
#define NUM_LEDS 9
#define DATA_PIN 11
#define CLOCK_PIN 11
#define JOY_X A5
#define JOY_Y A4
#define SW A3

#define TIPKA_0 0xE916FF00
#define TIPKA_100PLUS 0xE619FF00
#define TIPKA_200PLUS 0xF20DFF00
#define TIPKA_1 0xF30CFF00
#define TIPKA_2 0xE718FF00
#define TIPKA_3 0xA15EFF00
#define TIPKA_4 0xF708FF00
#define TIPKA_5 0xE31CFF00
#define TIPKA_6 0xA55AFF00
#define TIPKA_7 0xBD42FF00
#define TIPKA_8 0xAD52FF00
#define TIPKA_9 0xB54AFF00

CRGB leds[NUM_LEDS];

int pozicija = 0;
int onoff = 0;
int joy_sw_now = 0;
int svetlost = 0;
bool power = 1;

const int rs = 10, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

ThreeWire myWire(9,8,7); // DAT, CLK, RST
RtcDS1302<ThreeWire> Rtc(myWire);

void setup()
{
  Rtc.Begin();
  Serial.begin(115200);
  IrReceiver.begin(A0, ENABLE_LED_FEEDBACK);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  lcd.begin(16, 2);
  lcd.print("Jaka Cernetic");

  pinMode(SW, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  onoff = digitalRead(SW);
}

void loop()
{
  int joy_x = analogRead(JOY_X);
  int joy_y = analogRead(JOY_Y);
  onoff = digitalRead(SW);

  if (onoff == LOW)
  {
    if (power == 1)
    {
      FastLED.clear();
      power = 0;
    }
    else
    {
      FastLED.show();
      power = 1;
    }
  }

  svetlost = joy_y / 4;
  FastLED.setBrightness(svetlost);
  FastLED.show();

  RtcDateTime now = Rtc.GetDateTime();

  lcd.setCursor(0,1);
  lcd.print("Ura:");
  lcd.print(now.Hour());
  lcd.print(":");
  lcd.print(now.Minute());

  if (IrReceiver.decode())
  {
    unsigned long koda = IrReceiver.decodedIRData.decodedRawData;
    switch (koda)
    {
    case TIPKA_1:
      IZPISI_TIPKO(TIPKA_1)
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Red;
      leds[3] = CRGB::Red;
      leds[4] = CRGB::Red;
      leds[5] = CRGB::Red;
      leds[6] = CRGB::Red;
      leds[7] = CRGB::Red;
      leds[8] = CRGB::Red;
      FastLED.show();
      lcd.clear();
      lcd.print("Red");
      break;
    case TIPKA_2:
      IZPISI_TIPKO(TIPKA_2)
      leds[0] = CRGB::Green;
      leds[1] = CRGB::Green;
      leds[2] = CRGB::Green;
      leds[3] = CRGB::Green;
      leds[4] = CRGB::Green;
      leds[5] = CRGB::Green;
      leds[6] = CRGB::Green;
      leds[7] = CRGB::Green;
      leds[8] = CRGB::Green;
      FastLED.show();
      lcd.clear();
      lcd.print("Green");
      break;
    case TIPKA_3:
      IZPISI_TIPKO(TIPKA_3)
      leds[0] = CRGB::Blue;
      leds[1] = CRGB::Blue;
      leds[2] = CRGB::Blue;
      leds[3] = CRGB::Blue;
      leds[4] = CRGB::Blue;
      leds[5] = CRGB::Blue;
      leds[6] = CRGB::Blue;
      leds[7] = CRGB::Blue;
      leds[8] = CRGB::Blue;
      FastLED.show();
      lcd.clear();
      lcd.print("Blue");
      break;
    case TIPKA_4:
      IZPISI_TIPKO(TIPKA_4)
      leds[0] = CRGB::White;
      leds[1] = CRGB::White;
      leds[2] = CRGB::White;
      leds[3] = CRGB::White;
      leds[4] = CRGB::White;
      leds[5] = CRGB::White;
      leds[6] = CRGB::White;
      leds[7] = CRGB::White;
      leds[8] = CRGB::White;
      FastLED.show();
      lcd.clear();
      lcd.print("White");
      break;
    case TIPKA_5:
      IZPISI_TIPKO(TIPKA_5)
      leds[0] = CRGB::Black;
      leds[1] = CRGB::Black;
      leds[2] = CRGB::Black;
      leds[3] = CRGB::Black;
      leds[4] = CRGB::Black;
      leds[5] = CRGB::Black;
      leds[6] = CRGB::Black;
      leds[7] = CRGB::Black;
      leds[8] = CRGB::Black;
      FastLED.show();
      lcd.clear();
      lcd.print("Off");
      break;
    case TIPKA_6:
      IZPISI_TIPKO(TIPKA_6)
      leds[0] = CRGB::Yellow;
      leds[1] = CRGB::Yellow;
      leds[2] = CRGB::Yellow;
      leds[3] = CRGB::Yellow;
      leds[4] = CRGB::Yellow;
      leds[5] = CRGB::Yellow;
      leds[6] = CRGB::Yellow;
      leds[7] = CRGB::Yellow;
      leds[8] = CRGB::Yellow;
      FastLED.show();
      lcd.clear();
      lcd.print("Yellow");
      break;
    case TIPKA_7:
      IZPISI_TIPKO(TIPKA_7)
      leds[0] = CRGB::Purple;
      leds[1] = CRGB::Purple;
      leds[2] = CRGB::Purple;
      leds[3] = CRGB::Purple;
      leds[4] = CRGB::Purple;
      leds[5] = CRGB::Purple;
      leds[6] = CRGB::Purple;
      leds[7] = CRGB::Purple;
      leds[8] = CRGB::Purple;
      FastLED.show();
      lcd.clear();
      lcd.print("Purple");
      break;
    case TIPKA_8:
      IZPISI_TIPKO(TIPKA_8)
      leds[0] = CRGB::Red;
      leds[1] = CRGB::Orange;
      leds[2] = CRGB::Yellow;
      leds[3] = CRGB::White;
      leds[4] = CRGB::Cyan;
      leds[5] = CRGB::Blue;
      leds[6] = CRGB::Green;
      leds[7] = CRGB::Purple;
      leds[8] = CRGB::DarkRed;
      FastLED.show();
      lcd.clear();
      lcd.print("Rainbow");
      break;
    case TIPKA_9:
      IZPISI_TIPKO(TIPKA_9)
      leds[0] = CRGB::Cyan;
      leds[1] = CRGB::Cyan;
      leds[2] = CRGB::Cyan;
      leds[3] = CRGB::Cyan;
      leds[4] = CRGB::Cyan;
      leds[5] = CRGB::Cyan;
      leds[6] = CRGB::Cyan;
      leds[7] = CRGB::Cyan;
      leds[8] = CRGB::Cyan;
      FastLED.show();
      lcd.clear();
      lcd.print("Cyan");
      break;
    default:
      if (koda != 0)
        Serial.println(koda, HEX);
      break;
    }
    IrReceiver.resume();
  }
}
