#include "timer.h"
#include "Arduino.h"

myTimer::myTimer() {
    Serial.println("myTimer constructor");
}

void printHello() {
    Serial.println("Hello");
};

void printHello2() {
    Serial.println("Hello2");
};

void myTimer::setTimer(unsigned long _interval, int _count) {
    interval = _interval;
    count = _count;
}

void myTimer::startTimer() {
    start = millis();
    nextCall = start + interval;
}

void myTimer::checkTimer() {
    if (millis() >= nextCall) {
        if (count > 0) {
            count--;
            nextCall = nextCall + interval;
            if (cb != nullptr)
                cb();
            Serial.println(count);
        } else {
            return;
        }
    }
}
