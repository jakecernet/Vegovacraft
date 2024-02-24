#include <Arduino.h>
#include <button.h>
#include <timer.h>

button b1(7);

void obPritisku() {
    Serial.print("Gumb je bil pritisnjen. ");
}

void obSpustu() {
    digitalWrite(13, !digitalRead(13));
    Serial.print("Gumb je bil spuščen. ");
    Serial.println(digitalRead(13));
}

void setup() {
    Serial.begin(115200);
    b1.onPress = obPritisku;
    b1.onRelease = obSpustu;
    pinMode(13, OUTPUT);
    Serial.print("število gumbov: ");
    Serial.println(button::numButtons);
}

void loop() {
    b1.check();
}
