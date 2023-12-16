#include "LiquidCrystal.h"
#include "RtcDS1302.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "IRremote.h"
#include "FastLED.h"

#define NUM_LEDS 9
CRGB leds[NUM_LEDS];
#define LED_PIN A4

byte hh, mm, ss, mmm, dd; // ure, minute, sekunde, milisekunde, dnevi

byte znak_bar2[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111};
byte znak_bar3[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111};
byte znak_bar4[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111};
byte znak_bar5[8] = {0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte znak_bar6[8] = {0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte znak_bar7[8] = {0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};

struct
{
  byte ahh, amm, ass;
  byte alarm_vkljucen = false;
  byte alarm_sprozen = false;
  byte jakost_zaslona = 5;
  // todo implementiramo kontrolno vsoto
  byte kontrolna_vsota = 0;
} nastavitve;

void nastavi_alarm(byte h, byte m, byte s);

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
#define SCLK A2 // CLK
#define IO A1   // DAT
#define CE A0   // RST

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

void izpisi_alarm()
{
  char buffer[50];
  snprintf(buffer, sizeof buffer, "%02d:%02d:%02d", nastavitve.ahh, nastavitve.amm, nastavitve.ass);
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
  IrReceiver.begin(A5, true);
  uint8_t prebrano;
  prebrano = Rtc.GetMemory((uint8_t *)&nastavitve, sizeof nastavitve);
  analogWrite(9, map(nastavitve.jakost_zaslona, 0, 9, 0, 255));

  lcd.begin(16, 2);
  lcd.createChar(0, znak_bar2);
  lcd.createChar(1, znak_bar3);
  lcd.createChar(2, znak_bar4);
  lcd.createChar(3, znak_bar5);
  lcd.createChar(4, znak_bar6);
  lcd.createChar(5, znak_bar7);

  printActiveIRProtocols(&Serial);

  Serial.print("Jakost zaslona: ");
  Serial.println(nastavitve.jakost_zaslona);

  Serial.print("Prebrano ");
  if (!(nastavitve.ahh < 24 && nastavitve.amm < 60 && nastavitve.ass < 60))
  {
    nastavitve.alarm_vkljucen = false;
    nastavitve.alarm_sprozen = false;
    nastavitve.ahh = 0;
    nastavitve.amm = 0;
    nastavitve.ass = 0;
    prebrano = Rtc.SetMemory((uint8_t *)&nastavitve, sizeof nastavitve);
    Serial.print("\nAlarm resetiran\n");
  }
  Serial.print(prebrano);
  Serial.print(" znakov iz pomnilnika RTC");

  Rtc.Begin();
  izpisi_uro();
  pinMode(13, OUTPUT);
  // stanje led preberemo iz EEPROMa
  stanje_led = EEPROM.read(0);

  lcd.print("Hello!");
  cas = millis();

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, sizeof leds / sizeof leds[0]);
  memset(leds, 0, sizeof leds);
  FastLED.show();
}

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

  if (!((h >= 0) && (h < 24)))
    return false;
  if (!((m >= 0) && (h < 60)))
    return false;
  if ((s < 0) || (s >= 60))
    return false;

  *hh = h;
  *mm = m;
  *ss = s;
  return true;
}

void nastavi_alarm(byte h, byte m, byte s)
{
  nastavitve.ahh = h;
  nastavitve.amm = m;
  nastavitve.ass = s;
  nastavitve.alarm_vkljucen = true;
  char buffer[9];
  snprintf(buffer, sizeof buffer, "%02d:%02d:%02d", nastavitve.ahh, nastavitve.amm, nastavitve.ass);
  Serial.println(buffer);

  nastavitve.alarm_vkljucen = true;
  Rtc.SetMemory((uint8_t *)&nastavitve, sizeof nastavitve);
}

void izkljuci_alarm()
{
  nastavitve.alarm_vkljucen = false;
}

bool preveri_alarm()
{
  if (!nastavitve.alarm_vkljucen)
    return false;
  rtc_dt = Rtc.GetDateTime();

  int now = rtc_dt.Hour() * 60 * 60 +
            rtc_dt.Minute() * 60 +
            rtc_dt.Second();

  int alarm = nastavitve.ahh * 60 * 60 +
              nastavitve.amm * 60 +
              nastavitve.ass;

  // Serial.print(now);
  // Serial.print(" : ");
  // Serial.println(alarm);

  if (now < alarm)
    return false;
  if (now > alarm + 180)
    return false;
  return true;
};

/// -----
/// @brief Funkcija preverja, ali je dani niz med prepoznanimi ukazi
/// in kateri po vrsti je
/// @param Niz niz znakov, ki vsebuje ukaz in parametre
/// @returns Kateri ukaz po vrsti je
int doloci_ukaz(char niz[])
{
  uint8_t preverjam = 0;
  uint8_t najden = 0;
  // shortanje operatorjev ( 0 | 0 | 1 | 0 | 0 | 1)
  if (
      (preverjam++, (strcmp(vnos.niz, "ON") == 0)) ||
      (preverjam++, (strcmp(vnos.niz, "OFF") == 0)) ||
      (preverjam++, (strcmp(vnos.niz, "URA") == 0)) ||
      (preverjam++, (strncmp(vnos.niz, "URA ", 4) == 0)) ||
      (preverjam++, (strcmp(vnos.niz, "ALARM") == 0)) ||
      (preverjam++, (strncmp(vnos.niz, "ALARM ", 6) == 0)) ||
      (preverjam++, (strcmp(vnos.niz, "JAKOST") == 0)) ||
      (preverjam++, (strncmp(vnos.niz, "JAKOST ", 7) == 0)) ||
      0)
    najden = preverjam;

  return najden;
}

char buffer[20];
byte graf_pos = 0;
unsigned char graf_znaki[9] = {' ', '_', 0b00000000, 1, 2, 3, 4, 5, 0b11111111};
byte graf[16];

bool olddecode = false;
int16_t lastCommand;

byte smer = 1;
byte pozicija = 0;

// brali bomo s serijskega vhoda vse dokler uporabnik ne pošlje tipke <enter> ali pa preberemo 20 znakov.
void loop()
{
  {
    leds[pozicija] = CRGB::Red;

    if (pozicija > 0)
    {
      leds[pozicija - 1] = 0x200000;
    }

    if (pozicija > 1)
    {
      leds[pozicija - 2] = 0x200000;
    }

    if (pozicija < NUM_LEDS - 1)
    {
      leds[pozicija + 1] = 0x080000;
    }

    if (pozicija < NUM_LEDS - 2)
    {
      leds[pozicija + 2] = 0x080000;
    }

    FastLED.show();
    leds[pozicija] = CRGB::Black;
    leds[pozicija - 1] = CRGB::Black;
    leds[pozicija + 1] = CRGB::Black;
    leds[pozicija - 2] = CRGB::Black;
    leds[pozicija + 2] = CRGB::Black;
    pozicija = pozicija + smer;

    //cylon eye - Če je pozicija 0 ali 9, spremeni smer
    if (pozicija == 0 || pozicija == NUM_LEDS - 1)
    {
      smer = -smer;
    }
  }

  if (IrReceiver.decode() && !olddecode)
  {
    Serial.print("Prebrano: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    lastCommand = IrReceiver.decodedIRData.command;

    lcd.setCursor(0, 0);
    lcd.print(IrReceiver.decodedIRData.command, HEX);

    olddecode = true;

    IrReceiver.resume();
  }
  else
  {
    olddecode = false;
  }

  if (olddecode)
  {
    switch (lastCommand)
    {
    case 0x07:
      if (nastavitve.jakost_zaslona > 0)
      {
        nastavitve.jakost_zaslona--;
        analogWrite(9, map(nastavitve.jakost_zaslona, 0, 9, 0, 255));
      }
      break;
    case 0x15:
      if (nastavitve.jakost_zaslona < 9)
      {
        nastavitve.jakost_zaslona++;
        analogWrite(9, map(nastavitve.jakost_zaslona, 0, 9, 0, 255));
      }
      break;
    default:
      break;
    }
  }

  vnos_niza(vnos);
  if (vnos.niz_vnesen)
  {
    int ukaz = doloci_ukaz(vnos.niz);
    Serial.print("Vneseni ukaz ustreza pogoju stevilka: ");
    Serial.print(ukaz);
    Serial.println(".");

    vnos.niz_vnesen = false;

    switch (ukaz)
    {
    case 1: // LED ON
      Serial.println("\nLED zdaj utripa");
      stanje_led = HIGH;
      // stanje si zapomnimo v EEPROM
      EEPROM.write(0, stanje_led);
      break;
    case 2: // LED OFF
      Serial.println("\nLED zdaj ne utripa več");
      stanje_led = LOW;
      // stanje si zapomnimo v EEPROM
      EEPROM.write(0, stanje_led);
      break;
    case 3:
      Serial.print("\n");
      izpisi_uro();
      break;
    case 4:
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
      break;
    case 5:
      Serial.print("\n Alarm je nastavljen ob ");
      izpisi_alarm();
      break;
    case 6:
      // če dolžina niza ni 12 in
      if (strlen(vnos.niz) == 14)
      { // ALARM 10:00:00
        // if (ali_je_pravilna_ura(&vnos.niz[6]))
        if (ali_je_pravilna_ura(vnos.niz + 6, 8, // +6 zaradi dolžine
                                &nastavitve.ahh,
                                &nastavitve.amm,
                                &nastavitve.ass))
        {
          nastavi_alarm(nastavitve.ahh, nastavitve.amm, nastavitve.ass);
        }
        else
        {
          Serial.println("Alarm ni pravilno vnešen");
        }
      }
      else
      {
        Serial.println("\nParameter ukaza ni pravi. ALARM hh:mm:ss z vodilnimi ničlami.");
      }
      break;
    case 7:
      Serial.print("\n Jakost zaslona: ");
      Serial.print(nastavitve.jakost_zaslona);
      Serial.print(".");
      break;
    case 8: // JAKOST 6
      if (strlen(vnos.niz) != 8)
      {
        Serial.print("Napačno vnesen ukaz. Primer: JAKOST 5");
        break;
      }
      if ((vnos.niz[7] < '0') || (vnos.niz[7] > '9'))
      {
        Serial.println("Parameter ni dovoljen znak. Mora biti številka.");
        break;
      }
      nastavitve.jakost_zaslona = vnos.niz[7] - 48; // zdaj bo vrednost od 0 do 9
      // potrebujemo vrednost od 0 do 255

      Rtc.SetMemory((uint8_t *)&nastavitve, sizeof nastavitve);
      analogWrite(9, map(nastavitve.jakost_zaslona, 0, 9, 0, 255));
      break;
    default:
      // drugače pa samo izpišemo, kaj je {uporabnik vnesel
      Serial.print("\nVnesli ste niz: ");
      Serial.println(vnos.niz);
      Serial.print("\nDolzina je bila ");
      Serial.println(strlen(vnos.niz));
      break;
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

  lcd.setCursor(4, 0); // postavimo v spodnjo vrstico
  rtc_dt = Rtc.GetDateTime();

  snprintf(buffer, 15, "[%c] %02d:%02d:%02d", preveri_alarm() ? 'A' : ' ', rtc_dt.Hour(), rtc_dt.Minute(), rtc_dt.Second());
  lcd.print(buffer);

  lcd.setCursor(0, 1);
  byte osvetlitev = map(analogRead(A3), 50, 725, 1, 8);
  // lcd.print((char)graf_znaki[osvetlitev]);
  graf_pos = (graf_pos + 1) % 16;
  graf[graf_pos] = osvetlitev;
  for (int i = 0; i < 16; i++)
  {
    lcd.print((char)graf_znaki[graf[(i + graf_pos) % 16]]);
  }
  delay(80);
}