#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
}

// null terminated string; to je niz znakov, ki se konča z vrednostjo 0
char buffer[21]; // rezerviramo 20 znakov za znake, ki jih bomo prebrali s serijskega vmesnika, začenjamo šteti od 0, en znak rezerviramo za null
                 // buffer[0] je prvi znak, buffer[1] je drugi znak, itd.

int i = 0;

// brali bomo s serijskega vmesnika vse dokler uporanik ne pritisne enter ali pa prebere 20 znakov
void loop()
{
  char c; // začasna spremenljivka

  while (Serial.available())
  {
    // preberemo znak iz serijskega vmesnika
    c = Serial.read();

    if ((c >= ' ') && (c <= 127))
    {
      Serial.print(c);
      buffer[i] = c;
      i++;
      if (i >= 20)
      {
        buffer[20] = 0; // na koncu dodamo še null
        Serial.print("\nVnesli ste:");
        Serial.println(buffer);
        i = 0;
      }
    }

    // če je znak enak enterju, backspaceu ali tabulatorju, ga ne dodamo v buffer
    if (c == 13)
    {
      buffer[i] = 0;
      Serial.println("\nVnesli ste:");
      Serial.println(buffer);
      i = 0;
    }

    // če je znak enak backspace
    if (c == 8)
    {
      Serial.print(c);
      Serial.print("  ");
      Serial.print(c);
      if (i > 0)
      {
        i = i - 1;
      }
    }

    // če je znak enak tabulatorju
    if (c == 9)
    {
      Serial.println("TAB");
    }

    // če je znak enak esc
    if (c == 27)
    {
      Serial.println("ESC");
      buffer[0] = 0;
      i = 0;
    }

    // če je znak enak presledku
    if (c == 32)
    {
      Serial.println("SPACE");
    }
  }

  // na koncu izpišemo vse prejete znake
  // Serial.println("");
  // Serial.println(buffer);
}