#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.cursor();
  lcd.blink();

  delay(1000);
  // Print a message to the LCD.
  lcd.print("\xE0To je pa eno daljse besedilo. Pravzaprav je zares dolgo.");
  delay(400);
}

void loop() {
  for (int i = 0; i < 24; i++) {
    lcd.scrollDisplayLeft();
    delay(400);
  }

  delay(2000);

  for (int i = 0; i < 24; i++) {
    lcd.scrollDisplayRight();
    delay(400);
  }

  delay(2000);
}