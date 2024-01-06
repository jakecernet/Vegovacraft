// callback je kazalec na funkcijo
// ta funkcija ne vrača ničesar in ne sprejema ničesar
typedef void (*callbackFunction)();

class myTimer {
    unsigned long start;    // časovna oznaka za začetek čakanja
    unsigned long interval; // časovni interval za čakanje
    int count;              // števec izvedb
    unsigned long nextCall; // kdaj bo naslednji klic

public:
    bool timerCaka; // ali čakamo na primeren trenutek za izvedbo
    callbackFunction cb;

    myTimer();
    void setTimer(unsigned long _interval, int _count);
    void startTimer();
    void checkTimer();
};

void printHello();
void printHello2();