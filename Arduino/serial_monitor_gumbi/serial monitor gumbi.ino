int gumblevi = 0;
int gumbdesni = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  gumblevi = !digitalRead(3);
  gumbdesni = 1 - digitalRead(12);

  int in = gumblevi && gumbdesni;
  int ali = gumblevi || gumbdesni;

  Serial.print("Levi: ");
  Serial.print(gumblevi + 2);
  Serial.print(", Desni: ");
  Serial.println(gumbdesni);

  delay(40);
}