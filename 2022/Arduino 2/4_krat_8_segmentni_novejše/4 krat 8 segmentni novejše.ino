#define SDP 9
#define SC 8
#define SD 7
#define SE 6
#define SB 5
#define SA 4
#define SF 3
#define SG 2

#define SKUPNA_D1 A0
#define SKUPNA_D2 A1
#define SKUPNA_D3 A2
#define SKUPNA_D4 A3

#define PRIZGANA_STEVKA HIGH  //ce dela na skupno katodo zamenjaj z HIGH
#define UGASNJENA_STEVKA LOW
#define NEGIRANO !  //vkljuci ustrezno vrstico

///                    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP    ABCDEFGP
byte stevke[10] = { 0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110 };

// priključki segmentov   A   B   C   D   E   F   G   DP
byte pini_segmentov[] = { SA, SB, SC, SD, SE, SF, SG, SDP };

void izberi_pozicijo(int pozicija) {
  digitalWrite(SKUPNA_D1, UGASNJENA_STEVKA);
  digitalWrite(SKUPNA_D2, UGASNJENA_STEVKA);
  digitalWrite(SKUPNA_D3, UGASNJENA_STEVKA);
  digitalWrite(SKUPNA_D4, UGASNJENA_STEVKA);

  if (pozicija == 1) {
    digitalWrite(SKUPNA_D1, PRIZGANA_STEVKA);
  } else if (pozicija == 2) {
    digitalWrite(SKUPNA_D2, PRIZGANA_STEVKA);
  } else if (pozicija == 3) {
    digitalWrite(SKUPNA_D3, PRIZGANA_STEVKA);
  } else if (pozicija == 4) {
    digitalWrite(SKUPNA_D4, PRIZGANA_STEVKA);
  }
}

void prikazi_cifro(int stevilka) {
  digitalWrite(SA, NEGIRANO(stevke[stevilka] & 0b10000000) > 0);
  digitalWrite(SB, NEGIRANO(stevke[stevilka] & 0b01000000) > 0);
  digitalWrite(SC, NEGIRANO(stevke[stevilka] & 0b00100000) > 0);
  digitalWrite(SD, NEGIRANO(stevke[stevilka] & 0b00010000) > 0);
  digitalWrite(SE, NEGIRANO(stevke[stevilka] & 0b00001000) > 0);
  digitalWrite(SF, NEGIRANO(stevke[stevilka] & 0b00000100) > 0);
  digitalWrite(SG, NEGIRANO(stevke[stevilka] & 0b00000010) > 0);
  digitalWrite(SDP, NEGIRANO(stevke[stevilka] & 0b00000001) > 0);
}


// TABELA ZA AND (IN) &&
// | A | B | A & B |
// | 0 | 0 |   0   |
// | 0 | 1 |   0   |
// | 1 | 0 |   0   |
// | 1 | 1 |   1   |


// PRIMER BINARNE OPERACIJE IN &
//    11111100  01100000
//  & 00010000  00010000
//  --------------------
//    00010000  00000000





void setup() {
  // put your setup code here, to run once:
  pinMode(SA, OUTPUT);
  pinMode(SB, OUTPUT);
  pinMode(SC, OUTPUT);
  pinMode(SD, OUTPUT);
  pinMode(SE, OUTPUT);
  pinMode(SF, OUTPUT);
  pinMode(SG, OUTPUT);
  pinMode(SDP, OUTPUT);

  pinMode(SKUPNA_D1, OUTPUT);
  pinMode(SKUPNA_D2, OUTPUT);
  pinMode(SKUPNA_D3, OUTPUT);
  pinMode(SKUPNA_D4, OUTPUT);

  izberi_pozicijo(1);
  prikazi_cifro(4);
}

void loop() {
  // put your main code here, to run repeatedly:

  int stevilo = millis() / 100;  //sekunde od reseta

  byte e = stevilo % 10;           // 3
  byte d = (stevilo / 10) % 10;    // 0
  byte s = (stevilo / 100) % 10;   // 2
  byte t = (stevilo / 1000) % 10;  // 0

  for (int i = 1; i < 5; i++) {
    izberi_pozicijo(i);
    if (i == 1)
      prikazi_cifro(e);
    else if (i == 2)
      prikazi_cifro(d);
    else if (i == 3)
      prikazi_cifro(s);
    else if (i == 4)
      prikazi_cifro(t);
    delay(1);
  }
}