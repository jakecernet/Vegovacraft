#include <Arduino.h>
#include <timer.h>
myTimer t;
myTimer u;

void setup() {
    Serial.begin(115200);

    t.timerCaka = true;

    t.cb = printHello;
    t.setTimer(1000, 1);
    t.startTimer();
}

void loop() {
    t.checkTimer();
}
