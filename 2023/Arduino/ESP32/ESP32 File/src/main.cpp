#include "FS.h"
#include "LittleFS.h"
#include <Arduino.h>

void setup() {
    LittleFS.begin(true);
    Serial.begin(921600);

    char datoteka[] = "/hello.txt";
    File dat = LittleFS.open(datoteka, "r");
    Serial.printf("Datoteka %s je dolga %d bytov.", datoteka, dat.size());
}

void loop() {
    delay(20000);
}