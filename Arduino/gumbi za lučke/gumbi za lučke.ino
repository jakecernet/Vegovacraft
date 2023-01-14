int zeleni = 0;
int rumeni = 0;
int rdeci = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);

  pinMode(6, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  zeleni = digitalRead(6);
  rumeni = digitalRead(9);
  rdeci = digitalRead(11);

  Serial.print(zeleni);
  Serial.print(rumeni);
  Serial.println(rdeci);

  if(zeleni == 0){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }

  if(rumeni == 0){
    digitalWrite(4, HIGH);
  }
  else{
    digitalWrite(4, LOW);
  }

  if(rdeci == 0){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }
  
}
