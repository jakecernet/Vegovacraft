int stanje = 0;
int gumb = 0;
int stariGumb = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(3, OUTPUT);   // ARD
  pinMode(5, OUTPUT);   //ARU
  pinMode(7, OUTPUT);   //AZE
  pinMode(9, OUTPUT);   //PR
  pinMode(10, OUTPUT);  //PZ
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(11, INPUT_PULLUP);  // GUMB PEŠCI
  pinMode(12, INPUT_PULLUP);  //GUMB RUMENA

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  gumb = digitalRead(12);

  if (stariGumb != gumb && !gumb) {
    stanje = !stanje;
  }

  stariGumb = gumb;

  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);

  while (stanje) {
    digitalWrite(5, HIGH);
    delay(500);
    digitalWrite(5, LOW);
    delay(500);
  }

  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);

  while (!digitalRead(11)) {

    delay(500);

    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);

    delay(500);

    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);

    delay(500);

    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);

    delay(4000);
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);

    delay(500);

    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);

    delay(1000);
  }
}