#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte modri_tag[4] = {0xBD, 0x99, 0xFE, 0x30};

const int rs = 7, en = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  rfid.PCD_Init();    // Init MFRC522
  Serial.println("RFID scanner started");
  lcd.begin(16, 2);
  lcd.print("Jaka Cernetic");
}

void loop()
{
  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }

  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.println("Card UID:");
  Serial.print(rfid.uid.size);
  Serial.print(" bytov.");

  for (int i = 0; i < rfid.uid.size; i++)
  {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }

  if (rfid.uid.size != 4)
  {
    return;
  }

  Serial.println();

  bool prava_karta = true;

  if (rfid.uid.uidByte[0] == modri_tag[0] &&
      rfid.uid.uidByte[1] == modri_tag[1] &&
      rfid.uid.uidByte[2] == modri_tag[2] &&
      rfid.uid.uidByte[3] == modri_tag[3])
  {
    lcd.clear();
    lcd.print("Modri tag");
    Serial.println("Modri tag");
  }
  else
  {
    lcd.clear();
    lcd.print("Ena druga kartica");
    Serial.println("Ena druga kartica");
  }

  Serial.println();

  delay(500);
}
