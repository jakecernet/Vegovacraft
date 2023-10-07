#include <Arduino.h>

#define color_red "\x1B[31m"
#define color_white "\x1B[37m"
#define color_yellow "\x1B[33m"
#define color_reset "\x1B[0m"

#define GOTOXY (x, y) "\e[" #y ";" #x "H"
#define clear_screen "\x1b[0K"
#define clr_scr "\x1b[2J"

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  serial.begin(115200);
  Serial.print(clr_scr);
};

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(GOTOXY(1, 1) color_white "led " color_yellow "on ");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(GOTOXY(5, 1) color_red "led");
  delay(1000);
};
