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

/*
 * Nastavi časovni interval in število izvedb.
 *
 * @param _interval časovni interval v milisekundah
 * @param _count število izvedb
 */
void myTimer::setTimer(unsigned long _interval, int _count) {
    interval = _interval;
    count = _count;
}

/*
 * Začne čakati na pretečen časovni interval.
 */

void myTimer::startTimer() {
    start = millis();
    nextCall = start + interval;
}

/*
 * Preveri, ali je časovni interval potekel.
 * Če je, izvede funkcijo, ki je bila določena s pomočjo kazalca na funkcijo.
 */

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
