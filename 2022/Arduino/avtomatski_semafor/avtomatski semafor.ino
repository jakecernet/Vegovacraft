#define zelena 11
#define rumena 12
#define rdeca 13
#define pesz 10
#define pesr 9

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(rdeca, HIGH);
  digitalWrite(pesr, HIGH);
  delay(1000);
  digitalWrite(pesz, HIGH);
  digitalWrite(pesr, LOW);
  delay(5000);
  digitalWrite(pesr, HIGH);
  digitalWrite(pesz, LOW);
  delay(1000);
  digitalWrite(rumena, HIGH);
  delay(800);
  digitalWrite(rdeca, LOW);
  digitalWrite(rumena, LOW);
  digitalWrite(zelena, HIGH);
  delay(7000);
  digitalWrite(zelena, LOW);
  digitalWrite(rumena, HIGH);
  delay(1000);
  digitalWrite(rumena, LOW);
}
