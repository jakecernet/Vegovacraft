#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop()
{
  char c;

  while (Serial.available())
  {
    c = Serial.read();
    Serial.print(c, HEX);
    Serial.print(" ");
  }
}