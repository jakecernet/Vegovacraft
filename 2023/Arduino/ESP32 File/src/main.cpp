#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

void setup() {
    LittleFS.begin();
    Serial.begin(912600);

    char datoteka[] = "/data/hello.txt";
    File root = LittleFS.open(datoteka, "r");
    Serial.printf("Datoteka %s ima %d bajtova.\n", datoteka, root.size());

    for (int i = 0; i < 10; i++) {
        String s = root.readStringUntil('\n');
        Serial.println(s);
    }

    File dat = LittleFS.open("/data/there.txt", "r");
    dat.println("chip model: " + String(ESP.getChipModel()));
}

void loop() {
}