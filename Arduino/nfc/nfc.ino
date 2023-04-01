#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9

#define SOUND 2
#define RED A4
#define GREEN A5

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte modri_tag[4] = {0xBD, 0x99, 0xFE, 0x30};
byte dijaska[4] = {0x89, 0x8D, 0x79, 0x5E};
byte woop[4] = {0x0E, 0x2E, 0xA3, 0x45};

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void success(){
  tone(SOUND, 400);
  delay(200);
  tone(SOUND, 800);
  delay(200);
  tone(SOUND, 1200);
  delay(200);
  noTone(SOUND);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
}

void fail(){
  tone(SOUND, 2000);
  delay(200);
  tone(SOUND, 5000);
  delay(100);
  noTone(SOUND);
  digitalWrite(RED, HIGH);
}

void setup()
{
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  rfid.PCD_Init();    // Init MFRC522
  Serial.println("RFID scanner started");
  lcd.begin(16, 2);
  lcd.print("Jaka Cernetic");

  pinMode(2, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
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

  if (rfid.uid.uidByte[0] == modri_tag[0] &&
      rfid.uid.uidByte[1] == modri_tag[1] &&
      rfid.uid.uidByte[2] == modri_tag[2] &&
      rfid.uid.uidByte[3] == modri_tag[3])
  {
    success();
    lcd.clear();
    lcd.print("Modri tag");
    Serial.println("Modri tag");
  }
  else
  {
    if (rfid.uid.uidByte[0] == dijaska[0] &&
        rfid.uid.uidByte[1] == dijaska[1] &&
        rfid.uid.uidByte[2] == dijaska[2] &&
        rfid.uid.uidByte[3] == dijaska[3])
    {
      success();
      lcd.clear();
      lcd.print("Dijaska");
      Serial.println("Dijaska");
    }
    else
    {
      if (rfid.uid.uidByte[0] == woop[0] &&
          rfid.uid.uidByte[1] == woop[1] &&
          rfid.uid.uidByte[2] == woop[2] &&
          rfid.uid.uidByte[3] == woop[3])
      {
        success();
        lcd.clear();
        lcd.print("Woop woop");
        Serial.println("Woop woop");
      }
      else
      {
        fail();
        lcd.clear();
        lcd.print("Neznana karta");
      }
    }
  }

  Serial.println();

  delay(500);
}
