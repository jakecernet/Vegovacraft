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

ThreeWire myWire(9, 8, 7); // DAT, CLK, RST
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

int count = 0;

void displayLED(CRGB color)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color; 
  }
}

void loop()
{
  int joy_x = analogRead(JOY_X);
  int joy_y = analogRead(JOY_Y);
  onoff = digitalRead(SW);

  svetlost = joy_y / 4;

  if (onoff == LOW)
  {
    if (power == 1)
    {
      power = 0;
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Off");
    }
    else
    {
      power = 1;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("On");
    }
  }

  if (power == 0)
  {
    FastLED.setBrightness(0);
  }
  else
  {
    FastLED.setBrightness(svetlost);
  }

  RtcDateTime now = Rtc.GetDateTime();

  lcd.setCursor(0, 1);
  lcd.print("Ura: ");
  lcd.print(now.Hour());
  lcd.print(":");
  lcd.print(now.Minute());
  lcd.print(":");
  lcd.print(now.Second());

  lcd.setCursor(0, 0);
  lcd.print("Datum: ");
  lcd.print(now.Day());
  lcd.print(".");
  lcd.print(now.Month());
  lcd.print(".");
  lcd.print(now.Year());

  if (IrReceiver.decode())
  {
    unsigned long koda = IrReceiver.decodedIRData.decodedRawData;
    switch (koda)
    {
    case TIPKA_1:
      IZPISI_TIPKO(TIPKA_1)
      displayLED(CRGB::Red);
      break;
    case TIPKA_2:
      IZPISI_TIPKO(TIPKA_2)
      displayLED(CRGB::Green);
      break;
    case TIPKA_3:
      IZPISI_TIPKO(TIPKA_3)
      displayLED(CRGB::Blue);
      break;
    case TIPKA_4:
      IZPISI_TIPKO(TIPKA_4)
      displayLED(CRGB::White);
      break;
    case TIPKA_5:
      IZPISI_TIPKO(TIPKA_5)
      displayLED(CRGB::Black);
      break;
    case TIPKA_6:
      IZPISI_TIPKO(TIPKA_6)
      displayLED(CRGB::Yellow);
      break;
    case TIPKA_7:
      IZPISI_TIPKO(TIPKA_7)
      displayLED(CRGB::Purple);
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
      break;
    case TIPKA_9:
      IZPISI_TIPKO(TIPKA_9)
      displayLED(CRGB::Cyan);
      break;
    default:
      if (koda != 0)
        Serial.println(koda, HEX);
      break;
    }
    IrReceiver.resume();
  }
  FastLED.show();
}
