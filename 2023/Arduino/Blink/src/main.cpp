#include <Arduino.h>

#define color_red "\x1B[31m"
#define color_yellow "\x1B[33m"
#define color_reset "\x1B[0m"

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  serial.begin(115200);
};

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print(color_red "led on"color_reset);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print(color_yellow "led off" color_reset);
  delay(1000);
};
