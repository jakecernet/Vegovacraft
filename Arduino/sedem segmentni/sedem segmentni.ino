void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);  //DP
  pinMode(8, OUTPUT);  //C
  pinMode(7, OUTPUT);  //D
  pinMode(6, OUTPUT);  //E
  pinMode(5, OUTPUT);  //B
  pinMode(4, OUTPUT);  //A
  pinMode(3, OUTPUT);  //F
  pinMode(2, OUTPUT);  //G

  pinMode(12, INPUT_PULLUP);  //gumb
}

int pavza = 30;  //pavza vrednost
int delta = 10;
bool on = HIGH;
bool dele = 0;
bool prej = 0;

void loop() {
  // put your main code here, to run repeatedly:
  dele = digitalRead(12);  //preberemo stanje zdej

  if (dele != prej && prej != 0) {  //ali je bil gumb pritisnjen
    on = !on;
  }

  prej = dele;  //shranimo stanje za pol

  digitalWrite(8, on);   //prizgi C
  digitalWrite(5, LOW);  //ugasni B
  delay(pavza);          //delay :)
  digitalWrite(7, on);   //prizgi D
  digitalWrite(8, LOW);  //ugasni C
  delay(pavza);
  digitalWrite(6, on);   //prizgi E
  digitalWrite(7, LOW);  //ugasni D
  delay(pavza);
  digitalWrite(3, on);   //prizgi F
  digitalWrite(6, LOW);  //ugasni E
  delay(pavza);
  digitalWrite(4, on);   //prizgi A
  digitalWrite(3, LOW);  //ugasni F
  delay(pavza);
  digitalWrite(5, on);   //prizgi B
  digitalWrite(4, LOW);  //ugasni A
  delay(pavza);

  if (pavza > 100 || pavza < 20) {  //preveri če je pavza večja od 100 ali manjša od 20
    delta = -delta;
  }
  pavza += delta;
}