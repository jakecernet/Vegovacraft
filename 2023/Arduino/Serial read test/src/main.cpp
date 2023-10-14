#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
}

char buffer[20]; // rezerviramo 20 znakov za znake, ki jih bomo prebrali s serijskega vmesnika, začenjamo šteti od 0
//buffer[0] je prvi znak, buffer[1] je drugi znak, itd.

// brali bomo s serijskega vmesnika vse dokler uporanik ne pritisne enter ali pa prebere 20 znakov
void loop()
{
  int i = 0;

  char c; //začasna spremenljivka

  while (Serial.available())
  {
    //preberemo znak iz serijskega vmesnika
    c = Serial.read();

    if ((c >= ' ') && (c <= 127)){
      Serial.print(c);
      buffer[i] = c;
      i++;
      if (i >= 20){
        Serial.println("");
        Serial.println(buffer);
        i = 0;
      }
    }
  }

  //na koncu izpišemo vse prejete znake
  //Serial.println("");
  //Serial.println(buffer);
}