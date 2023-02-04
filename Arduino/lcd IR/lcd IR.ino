// include the library code:
#include <LiquidCrystal.h>
#include <IRremote.h>
//#define DECODE_LG

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define SPREJEMNIK_PIN A0


IRrecv sprejemnik(SPREJEMNIK_PIN);
decode_results rezultati;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("hello, world!");

  sprejemnik.enableIRIn();
  sprejemnik.blink13(true);
}

void loop() {
  if (sprejemnik.decode(&rezultati)) {
    Serial.println(rezultati.value, HEX);
    //sprejemnik.printIRResultShort(&Serial);

      switch (rezultati.decode_type){
              case NEC: Serial.println("NEC"); break ;
              case SONY: Serial.println("SONY"); break ;
              case RC5: Serial.println("RC5"); break ;
              case RC6: Serial.println("RC6"); break ;
              case SHARP: Serial.println("SHARP"); break ;
              case JVC: Serial.println("JVC"); break ;
              case SAMSUNG: Serial.println("SAMSUNG"); break ;
              case LG: Serial.println("LG"); break ;
              case WHYNTER: Serial.println("WHYNTER"); break ;
              case PANASONIC: Serial.println("PANASONIC"); break ;
              case DENON: Serial.println("DENON"); break ;
            default:
              case UNKNOWN: Serial.println("UNKNOWN"); break ;
            }

    switch (rezultati.value) {
      case 0xFFA25D: Serial.println("1"); break;
      case 0xFF629D: Serial.println("2"); break;
      case 0xFF18E7: Serial.println("^"); break;
      case 0xFF4AB5: Serial.println("v"); break;
      default: break;
    }
      
    sprejemnik.resume();
  }
}