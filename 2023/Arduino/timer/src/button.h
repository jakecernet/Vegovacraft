#include <Arduino.h>

typedef void (*buttonCallback)();

class button {

private:
    bool stanje;
    byte pin;
    bool negativeLogic;
    unsigned long nextChange;

public:
    button(byte a_pin, bool defaultPullup = true);
    void check();
    bool status();
    static int numButtons;

    buttonCallback onPress;
    buttonCallback onRelease;
};