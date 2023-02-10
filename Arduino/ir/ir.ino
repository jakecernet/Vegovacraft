#include <IRremote.hpp>
#define DECODE_NEC
/* #define MOJ_DALJINC 2

#if MOJ_DALJINC == 1
  #define TIPKA 0 
#elif MOJ_DALJINC == 2*/

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(A0, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long koda = IrReceiver.decodedIRData.decodedRawData;

    //Serial.println("Received");
    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
    switch (koda){
    case 0xF807FF00:
      Serial.println("-");
      break;
    case 0xEA15FF00:
      Serial.println("+");
      break;
    case 0xF609FF00:
      Serial.println("EQ");
      break;                
    default:
    if(koda != 0)Serial.println(koda, HEX);
      break;
    }

    IrReceiver.resume(); // Receive the next value
  }
}
