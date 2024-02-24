#include "LiquidCrystal.h"
#include "RtcDS1302.h"
#include <Arduino.h>
#include <EEPROM.h>

// struktura nosi s seboj podatke za opis nekega elementa
// nas element bo vnos preko serijskega vhoda
struct polje_vnosa_t
{
  byte dolzina;
  char niz[21];
  byte pozicija;
  bool niz_vnesen;
} vnos = {21, "", 0, false};

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
      // če smo prekoračili velikost vnosa, damo zvonček (bell)
      if (v.pozicija >= vnos.dolzina - 1)
      {
        // Serial.print('\a');
        // v nasprotnem primeru damo znak k nizu
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
      v.niz_vnesen = true;
      // Serial.print("\nVnesli ste: ");
      // Serial.println(v.niz);
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
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

// RTC pins
#define SCLK A0 // CLK
#define IO A1   // DAT
#define CE A2   // RST

bool stanje_led = HIGH; // bool je vrsta spremenljivke, ki je lahko true ali false
LiquidCrystal lcd(RS, EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

unsigned long cas;
RtcDateTime rtc_dt;
ThreeWire myWire(IO, SCLK, CE); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

int error_pos;

bool pravilna_ura(char *niz, byte len)
{
  Serial.print("Vnesli ste: ");
  Serial.println(niz);
  error_pos = 0;
  byte b = 0;
  while (b++ < len)
  {
    if (error_pos++, len != 8)
    {
      return false;
    }
    if (error_pos++, !(vnos.niz[2] == ':' || !(vnos.niz[5] == ':')))
    {
      return false;
    }
    {
      return false;
    }
    do
    {
      if (error_pos++, b == 2 || error_pos++, b == 5)
      {
        continue;
      }

      if (error_pos++, niz[b] < '0' || error_pos++, niz[b] > '9')
      {
        return false;
        Serial.println(b);
      }
    } while (b++ < len);
    b++;
  }
  return true;
}

void izpisi_uro()
{
  rtc_dt = Rtc.GetDateTime();

  char buffer[50];
  snprintf(buffer, sizeof buffer, "%02d:%02d:%02d", rtc_dt.Hour(), rtc_dt.Minute(), rtc_dt.Second());
  Serial.println(buffer);
}

void setup()
{
  Serial.begin(115200);

  Rtc.Begin();
  izpisi_uro();
  pinMode(13, OUTPUT);
  // stanje led preberemo iz EEPROMa
  stanje_led = EEPROM.read(0);

  lcd.begin(16, 2);
  lcd.print("Hello!");
  cas = millis();
}

void myDelay(int i)
{
  for (int j; j < i; j++)
  {
    delay(1);        // 1 ms
    vnos_niza(vnos); // pogledamo, če je kaj za vnesti
  }
}

byte hh, mm, ss, mmm, dd; // ure, minute, sekunde, milisekunde, dnevi
char buffer[20];

void loop()
{
  vnos_niza(vnos);
  if (vnos.niz_vnesen)
  {
    vnos.niz_vnesen = false;
    if (strcmp(vnos.niz, "ON") == 0)
    {
      Serial.println("\nLED zdaj utripa");
      stanje_led = HIGH;
      // stanje si zapomnimo v EEPROM
      EEPROM.write(0, stanje_led);
    }
    else if (strcmp(vnos.niz, "OFF") == 0)
    {
      Serial.println("\nLED zdaj ne utripa več");
      stanje_led = LOW;
      // stanje si zapomnimo v EEPROM
      EEPROM.write(0, stanje_led);
    }
    // tu preverjamo situacijo pri ukazu URA
    else if (strncmp(vnos.niz, "URA", 3) == 0)
    {
      if (strlen(vnos.niz) == 3)
        izpisi_uro();
    }
    if (strlen(vnos.niz) == 12)
    {
      if (pravilna_ura(vnos.niz + 4, 8))
      {
        Serial.println("Ura je pravilna");
      }
      else
      {
        Serial.print("Napaka pri vnosu ure na poziciji ");
        Serial.println(error_pos);
      }
    }
    else
    {
      Serial.println("Napaka pri vnosu ure");
    }
    {
      // drugače pa samo izpišemo, kaj je uporabnik vnesel
      Serial.print("\nVnesli ste niz: ");
      Serial.println(vnos.niz);
      Serial.print("\nDolzina je bila ");
      Serial.println(strlen(vnos.niz));
    }
  }

  cas = millis();   // tukaj dobimo celotni čas v ms
  mmm = cas % 1000; // samo milisekunde dobimo kot ostanek pri deljenju s 1000
  cas = cas / 100;  // cas zdaj delimo s 1000, da dobimo sekunde
  ss = cas % 60;    // samo sekunde bodo enake ostanku pri deljenju s 60
  cas /= 60;        // cas = cas / 60;  celimo cas s 60
  mm = cas % 60;
  cas /= 60;     // zdaj dobimo ure
  hh = cas % 24; // samo ure dobimo kot ostanek pri deljenju s 24
  cas /= 24;     // če zdaj cas delimo s 24, dobimo dneve
  dd = cas;      // mesecev in let se nam še ne da

  lcd.setCursor(0, 0); // postavimo v zgornjo vrstico
  snprintf(buffer, 15, "[%d] %02d:%02d:%02d.%1d", dd, hh, mm, ss, mmm / 100);
  lcd.print(buffer);

  lcd.setCursor(0, 1); // postavimo v spodnjo vrstico
  snprintf(buffer, 15, "[%X] %02X:%02X:%02X.%1X", dd, hh, mm, ss, mmm / 100);
  lcd.print(buffer);
}