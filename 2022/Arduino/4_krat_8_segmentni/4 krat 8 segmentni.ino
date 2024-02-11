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

#define PRIZGANA_STEVKA HIGH //ce dela na skupno katodo zamenjaj z HIGH
#define UGASNJENA_STEVKA LOW
#define NEGIRANO ! //vkljuci ustrezno vrstico

void izberi_samo_stevko(int stevka) {
  digitalWrite(SKUPNA_D1, UGASNJENA_STEVKA);
  digitalWrite(SKUPNA_D2, UGASNJENA_STEVKA);
  digitalWrite(SKUPNA_D3, UGASNJENA_STEVKA);
  digitalWrite(SKUPNA_D4, UGASNJENA_STEVKA);

  if (stevka == 1) {
    digitalWrite(SKUPNA_D1, PRIZGANA_STEVKA);
  }
  if (stevka == 2) {
    digitalWrite(SKUPNA_D2, PRIZGANA_STEVKA);
  }
  if (stevka == 3) {
    digitalWrite(SKUPNA_D3, PRIZGANA_STEVKA);
  }
  if (stevka == 4) {
    digitalWrite(SKUPNA_D4, PRIZGANA_STEVKA);
  }
}

void prikazi_cifro(byte A, byte B, byte C, byte D, byte E, byte F, byte G, byte DP) {
  digitalWrite(SA, NEGIRANO A);
  digitalWrite(SB, NEGIRANO B);
  digitalWrite(SC, NEGIRANO C);
  digitalWrite(SD, NEGIRANO D);
  digitalWrite(SE, NEGIRANO E);
  digitalWrite(SF, NEGIRANO F);
  digitalWrite(SG, NEGIRANO G);
  digitalWrite(SDP, NEGIRANO DP);

  return;
}

void prikazi_stevko(byte stevka) {
  if (stevka == 0) {
    prikazi_cifro(1, 1, 1, 1, 1, 1, 0, 0); //0
  }
  if (stevka == 1) {
    prikazi_cifro(0, 1, 1, 0, 0, 0, 0, 0); //1
  }
  if (stevka == 2) {
    prikazi_cifro(1, 1, 0, 1, 1, 0, 1, 0); //2
  }
  if (stevka == 3) {
    prikazi_cifro(1, 1, 1, 1, 0, 0, 1, 0); //3
  }
  if (stevka == 4) {
    prikazi_cifro(0, 1, 1, 0, 0, 1, 1, 0); //4
  }
  if (stevka == 5) {
    prikazi_cifro(1, 0, 1, 1, 0, 1, 1, 0); //5
  }
  if (stevka == 6) {
    prikazi_cifro(1, 0, 1, 1, 1, 1, 1, 0); //6
  }
  if (stevka == 7) {
    prikazi_cifro(1, 1, 1, 0, 0, 0, 0, 0); //7
  }
  if (stevka == 8) {
    prikazi_cifro(1, 1, 1, 1, 1, 1, 1, 0); //8
  }
  if (stevka == 9) {
    prikazi_cifro(1, 1, 1, 1, 0, 1, 1, 0); //9
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SDP, OUTPUT);
  pinMode(SC, OUTPUT);
  pinMode(SD, OUTPUT);
  pinMode(SE, OUTPUT);
  pinMode(SF, OUTPUT);
  pinMode(SG, OUTPUT);
  pinMode(SB, OUTPUT);
  pinMode(SA, OUTPUT);

  pinMode(SKUPNA_D1, OUTPUT);
  pinMode(SKUPNA_D2, OUTPUT);
  pinMode(SKUPNA_D3, OUTPUT);
  pinMode(SKUPNA_D4, OUTPUT);

  digitalWrite(SKUPNA_D1, PRIZGANA_STEVKA);
  digitalWrite(SKUPNA_D2, PRIZGANA_STEVKA);
  digitalWrite(SKUPNA_D3, PRIZGANA_STEVKA);
  digitalWrite(SKUPNA_D4, PRIZGANA_STEVKA);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 5; i++) {
    izberi_samo_stevko(i % 5);
    prikazi_stevko(i);
    delay(700);
  }
}