#include <Arduino.h>

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  serial.begin(115200);
};

void loop(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
};
