#include <Arduino.h>
#include <button.h>

button::button(byte a_pin, bool defaultPullup) {
    numButtons++;
    pin = a_pin;
    onPress = nullptr;
    onRelease = nullptr;
    if (defaultPullup) {
        pinMode(pin, INPUT_PULLUP);
        negativeLogic = true;
    } else {
        pinMode(pin, INPUT);
        negativeLogic = false;
    }

    stanje = digitalRead(pin);

    if (negativeLogic) {
        stanje = !stanje;
    }

    nextChange = millis() + 1;
};

bool button::status() {
    return stanje;
}

void button::check() {
    if (nextChange > millis()) {
        return;
    }

    bool novoStanje;
    novoStanje = digitalRead(pin);
    nextChange = millis() + 10;

    // če je gumb v negativni logiki, ga obrnemo
    if (negativeLogic) {
        novoStanje = !novoStanje;
    }

    // če se stanje ni spremenilo, gremo ven
    if (novoStanje == stanje) {
        stanje = novoStanje;
        return;
    }

    // če je sploh potrebno in če se je stanje spremenilo in če je gumb bil prej spuščen
    if ((onPress != nullptr) && (stanje != novoStanje) && (stanje == false)) {
        onPress();
    }

    // če je sploh potrebno in če se je stanje spremenilo in če je gumb bil prej pritisnjen
    if ((onPress != nullptr) && (stanje != novoStanje) && (stanje == true)) {
        onRelease();
    }

    stanje = novoStanje;
}