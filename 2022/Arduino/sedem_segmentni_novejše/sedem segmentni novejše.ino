#define SDP 9
#define SC 8
#define SD 7
#define SE 6
#define SB 5
#define SA 4
#define SF 3
#define SG 2
//                 A, B, C, D, E, F, G, DP

byte cifra_0[8] = { 1, 1, 1, 1, 1, 1, 0, 0 };

//Nastavi sedem segmenti LED, tako da gorijo segmenti v vrstnem redu kot je naveden spodaj.
void prikazi_cifro(byte A, byte B, byte C, byte D, byte E, byte F, byte G, byte DP) {
  digitalWrite(SA, A);
  digitalWrite(SB, B);
  digitalWrite(SC, C);
  digitalWrite(SD, D);
  digitalWrite(SE, E);
  digitalWrite(SF, F);
  digitalWrite(SG, G);
  digitalWrite(SDP, DP);

  return;
}

void prikazi_stevko(byte stevka) {
  if (stevka == 0) {
    prikazi_cifro(1, 1, 1, 1, 1, 1, 0, 0);  //0
  }
  if (stevka == 1) {
    prikazi_cifro(0, 1, 1, 0, 0, 0, 0, 0);  //1
  }
  if (stevka == 2) {
    prikazi_cifro(1, 1, 0, 1, 1, 0, 1, 0);  //2
  }
  if (stevka == 3) {
    prikazi_cifro(1, 1, 1, 1, 0, 0, 1, 0);  //3
  }
  if (stevka == 4) {
    prikazi_cifro(0, 1, 1, 0, 0, 1, 1, 0);  //4
  }
  if (stevka == 5) {
    prikazi_cifro(1, 0, 1, 1, 0, 1, 1, 0);  //5
  }
  if (stevka == 6) {
    prikazi_cifro(1, 0, 1, 1, 1, 1, 1, 0);  //6
  }
  if (stevka == 7) {
    prikazi_cifro(1, 1, 1, 0, 0, 0, 0, 0);  //7
  }
  if (stevka == 8) {
    prikazi_cifro(1, 1, 1, 1, 1, 1, 1, 0);  //8
  }
  if (stevka == 9) {
    prikazi_cifro(1, 1, 1, 1, 0, 1, 1, 0);  //9
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SDP, OUTPUT);  //DP
  pinMode(SC, OUTPUT);   //C
  pinMode(SD, OUTPUT);   //D
  pinMode(SE, OUTPUT);   //E
  pinMode(SB, OUTPUT);   //B
  pinMode(SA, OUTPUT);   //A
  pinMode(SF, OUTPUT);   //F
  pinMode(SG, OUTPUT);   //G
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int stevec = 0; stevec < 10; stevec++) {  //stevec++ poveča števec za ena
    prikazi_stevko(stevec);
    delay(500);
  }
  for (int stevec = 9; stevec >= 0; stevec--) {  //stevec++ poveča števec za ena
    prikazi_stevko(stevec);
    delay(3000);
  }
}