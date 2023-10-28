#include <Arduino.h>
#include <EEPROM.h>
#include "LiquidCrystal.h"

// struktura nosi s seboj podatke za opis nekega elementa
// nas element bo vnos preko serijskega vhoda
struct polje_vnosa_t
{
  byte dolzina;
  char niz[21];
  byte pozicija;
  bool niz_je_vnesen;
} vnos = {21, "", 0};

void vnos_niza(polje_vnosa_t &v)
{
  char c; // zacasni znak
  while (Serial.available())
  {
    // preberemo s serijskega vmesnika
    c = Serial.read();

    if ((c >= ' ') && (c <= 127))
    {
      Serial.print(c);
      // če smo prekoračili dolžino niza, potem damo zvonček
      if (v.pozicija >= vnos.dolzina - 1)
      {
        // Serial.print("\a");
      }
      else
      {
        v.niz[v.pozicija] = c;
        v.pozicija = v.pozicija + 1; // števec povečamo za 1
      }
    }
    // kaj pa če pošljemo <ENTER> ali druge tipke
    if (c == 13)
    {
      // Serial.print("<ENTER>");
      v.niz[v.pozicija] = 0;
      v.niz_je_vnesen = true;
      v.pozicija = 0; // števec resetiramo na 0
    }
    // BACKSPACE
    if (c == 8)
    {
      Serial.print(c);   // gremo en znak nazaj
      Serial.print(" "); // izpišemo presledek
      Serial.print(c);   // in gremo spet znak nazaj
      if (v.pozicija > 0)
        v.pozicija = v.pozicija - 1;
    }
    // TAB
    if (c == 9)
    {
      Serial.print("<TAB>");
    }
    // ESC
    if (c == 27)
    {
      Serial.print("<ESC>");
      v.niz[0] = 0;
      v.pozicija = 0;
    }
  }
}

#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

bool stanje_led = HIGH;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

long cas;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // preberemo stanje led iz eeproma
  stanje_led = EEPROM.read(0);

  lcd.begin(16, 2);
  lcd.print("Hello, world!");
  cas = millis();
}

// v myDelay je vnesen vnos_niza, da lahko vnosimo vrednosti medtem ko se delay izvaja
void myDelay(int ms)
{
  for (int i = 0; i < ms; i++)
  {
    delay(1);
    vnos_niza(vnos);
  }
}

byte hh, mm, ss, mmm, dd; // ure, minute, sekunde, milisekunde, dnevi
char buffer[20];

void loop()
{
  if (vnos.niz_je_vnesen)
  {
    vnos.niz_je_vnesen = false;
    if (strcmp(vnos.niz, "ON") == 0)
    {
      Serial.println("\nLED utripa");
      stanje_led = HIGH;
      // shrani stanje led v eeprom
      EEPROM.write(0, stanje_led);
    }
    else if (strcmp(vnos.niz, "OFF") == 0)
    {
      Serial.print("\nLED ne utripa");
      stanje_led = LOW;
      // shrani stanje led v eeprom
      EEPROM.write(0, stanje_led);
    }
    else
    {
      // izpisemo vneseno vrednost
      Serial.println("\nVnesli ste: ");
      Serial.println(vnos.niz);
    }
  }

  lcd.setCursor(0, 1);

  cas = millis() * 10;
  mmm = cas % 1000;
  ss = (cas / 1000) % 60;
  mm = (cas / 60000) % 60;
  hh = (cas / 3600000) % 24;
  dd = (cas / 86400000) % 365;

  snprintf(buffer, 13, "[%d] %02d:%02d:%02d", dd, hh, mm, ss);
  lcd.print(buffer);
}