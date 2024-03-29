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

void izpisi_uro()
{
  rtc_dt = Rtc.GetDateTime();

  char buffer[50];
  snprintf(buffer, sizeof buffer, "%02d:%02d:%02d", rtc_dt.Hour(), rtc_dt.Minute(), rtc_dt.Second());
  Serial.println(buffer);
}

void spremeni_uro(byte hh, byte mm, byte ss)
{
  rtc_dt = Rtc.GetDateTime();
  RtcDateTime nov = RtcDateTime(rtc_dt.Year(), rtc_dt.Month(), rtc_dt.Day(), hh, mm, ss);
  Rtc.SetDateTime(nov);
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

// v myDelay izvajamo vnos, ponavaljamo delay vsako milisekundo, tolikokrat, kot smo zahtevali v i
void myDelay(int i)
{
  for (int j; j < i; j++)
  {
    delay(1);        // 1 ms
    vnos_niza(vnos); // pogledamo, če je kaj za vnesti
  }
}

int error_pos;

bool ali_je_pravilna_ura(char *niz, byte len, byte *hh, byte *mm, byte *ss)
{ // 10:00:59  0x31 0x30 0x2B 0x30 0x30 0x2b 0x35 0x39
  byte b = 0;
  if (len != 8) // če je zadeva dolga različno od 8, sploh ne preverjamo, je zanič...
    return false;
  // če drugi in peti znak nista ':', niz tudi zanič...
  if ((niz[2] != ':') || (niz[5] != ':'))
    return false;
  do
  {
    // 2. in 5. znaka ne pregledujemo
    if ((b == 2) || (b == 5))
    {
      continue;
    }
    // če znak ni števka, je niz zanič
    if ((niz[b] < '0') || (niz[b] > '9'))
    {
      return false;
    }
  } while (++b < len); // najprej povečaj b in ponovi zanko, če je še vedno manjši od dolžine
  // // todo: še preverimo, če so ure, minute, sekunde v dovoljenem rangu
  byte h, m, s;

  //     '1'                  '0'
  h = (niz[0] - 48) * 10 + (niz[1] - 48); // 0 <= h < 24
  m = (niz[3] - 48) * 10 + (niz[4] - 48); // 0 <= m < 60
  s = (niz[6] - 48) * 10 + (niz[7] - 48); // 0 <= s < 60

  // Serial.print(h);
  // Serial.print(":");
  // Serial.print(m);
  // Serial.print(":");
  // Serial.println(s);
  if (!((h >= 0) && (h < 24)))
    return false;
  if (!((m >= 0) && (h < 60)))
    return false;
  if ((s < 0) || (s >= 60))
  {
    return false;
  }
  *hh = h;
  *mm = m;
  *ss = s;
  return true;
}

byte hh, mm, ss, mmm, dd; // ure, minute, sekunde, milisekunde, dnevi
byte ahh, amm, ass;
byte alarm_vkljucen = false;

void nastavi_alarm(byte h, byte m, byte s)
{
  ahh = h;
  amm = m;
  ass = s;
  alarm_vkljucen = true;
}

void izkljuci_alarm()
{
  alarm_vkljucen = false;
}

bool preveri_alarm()
{
  if (!alarm_vkljucen)
    return false;
  rtc_dt = Rtc.GetDateTime();

  int now = rtc_dt.Hour() * 60 * 60 +
            rtc_dt.Minute() * 60 +
            rtc_dt.Second();

  int alarm = hh * 60 * 60 +
              mm * 60 +
              ss;

  if (now < alarm)
    return false;
  if (now > alarm + 180)
    return false;
  return true;
};

char buffer[20];

// brali bomo s serijskega vhoda vse dokler uporabnik ne pošlje tipke <enter> ali pa preberemo 20 znakov.
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
      // URA HH:MM:SS
      // če dolžina niza ni 12 in
      if (strlen(vnos.niz) == 12)
      { // URA 10:00:00
        // if (ali_je_pravilna_ura(&vnos.niz[4]))
        if (ali_je_pravilna_ura(vnos.niz + 4, 8, &hh, &mm, &ss))
        {
          // Serial.println("Ura je pravilno vnešena");
          spremeni_uro(hh, mm, ss);
        }
        else
        {
          Serial.println("Ura ni pravilno vnešena");
        }
      }
      else
      {
        Serial.println("\nParameter ukaza ni pravi. URA hh:mm:ss z vodilnimi ničlami.");
      }
    }
    else
    {
      // drugače pa samo izpišemo, kaj je uporabnik vnesel
      Serial.print("\nVnesli ste niz: ");
      Serial.println(vnos.niz);
      Serial.print("\nDolzina je bila ");
      Serial.println(strlen(vnos.niz));
    }
  }
  // digitalWrite(13, stanje_led);
  // myDelay(1000);
  // digitalWrite(13, LOW);
  // myDelay(1000);
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

  // strncpy(buffer, "Vegovacraft",12);
  lcd.setCursor(0, 0); // postavimo v zgornjo vrstico
  snprintf(buffer, 15, "[%d] %02d:%02d:%02d.%1d", dd, hh, mm, ss, mmm / 100);
  lcd.print(buffer);

  lcd.setCursor(0, 1); // postavimo v spodnjo vrstico
  rtc_dt = Rtc.GetDateTime();

  // (bool) ? true : false
  // (2>1) ? 2 : 0     ....-> izraz vrne 2
  // (2<1) ? 2 : 0     ....-> izraz vrne 0
  // (2<1) ? 'A': 'B'     ....-> izraz vrne 'B'

  snprintf(buffer, 15, "[%c] %02d:%02d:%02d", preveri_alarm() ? 'A' : ' ', rtc_dt.Hour(), rtc_dt.Minute(), rtc_dt.Second());
  lcd.print(buffer);
}
