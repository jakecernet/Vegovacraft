#include <IRremote.hpp>
#define DECODE_NEC
#define MOJ_DALJINC 2
#define IZPISI_TIPKO(x) Serial.println(#x);

#if MOJ_DALJINC == 1
  #define TIPKA_ZVEZDICA 0xE916FF00 
  #define TIPKA_LOJTRA 0xF20DFF00
  #define TIPKA_0 0xE619FF00
  #define TIPKA_1 0xBA45FF00
  #define TIPKA_2 0xB946FF00
  #define TIPKA_3 0xB847FF00
  #define TIPKA_4 0xBB44FF00
  #define TIPKA_5 0xBF40FF00
  #define TIPKA_6 0xBC43FF00
  #define TIPKA_7 0xF807FF00
  #define TIPKA_8 0xEA15FF00
  #define TIPKA_9 0xF609FF00
#elif MOJ_DALJINC == 2
  #define TIPKA_ZVEZDICA 0
  #define TIPKA_LOJTRA 0
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
#endif

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(A0, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long koda = IrReceiver.decodedIRData.decodedRawData;

    // Serial.println("Dobil pritisk.");
    // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // Glede na prejeto kodo skočimo na določen del programa.
    switch (koda) {
      case TIPKA_1:
        IZPISI_TIPKO(TIPKA_1)
        break;
      case TIPKA_2:
        IZPISI_TIPKO(TIPKA_2)
        break;
      case TIPKA_3:
        IZPISI_TIPKO(TIPKA_3)
        break;
      case TIPKA_4:
        IZPISI_TIPKO(TIPKA_4)
        break;
      case TIPKA_5:
        IZPISI_TIPKO(TIPKA_5)
        break;
      case TIPKA_6:
        IZPISI_TIPKO(TIPKA_6)
        break;
      case TIPKA_7:
        IZPISI_TIPKO(TIPKA_7)
        break;
      case TIPKA_8:
        IZPISI_TIPKO(TIPKA_8)
        break;
      case TIPKA_9:
        IZPISI_TIPKO(TIPKA_9)
        break;
      default:
        if (koda != 0) Serial.println(koda, HEX);
        break;
    }

    IrReceiver.resume();
  }
}
