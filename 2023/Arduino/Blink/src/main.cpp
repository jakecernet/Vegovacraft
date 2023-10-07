#include <Arduino.h>

#define color_red "\x1B[31m"
#define color_yellow "\x1B[33m"
#define color_reset "\x1B[0m"

#define GOTOXY (x, y) "\e[" #y ";" #x "H"
#define clear_screen "\x1b[0K"
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  serial.begin(115200);
};

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(GOTOXY(1, 1) color_red "led on " color_reset);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(GOTOXY(1, 1) color_yellow "led off" clear_screen color_reset);
  delay(1000);
};
