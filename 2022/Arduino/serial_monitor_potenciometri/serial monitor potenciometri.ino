#define LED_A 2
#define LED_B 3
#define LED_C 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  //Serial.println("Min, Max, ADC, U"); // ADC - Analog to digital converter

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = analogRead(A0);

  if(i >= 750){
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, HIGH);
  }
  else if (i <= 250) {
    digitalWrite(LED_A, HIGH);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_C, LOW);
  }
  else {
    digitalWrite(LED_A, LOW);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_C, LOW);
  }

  Serial.print("Min:0, Max:1023, ADC:");
  Serial.print(i);
  Serial.print(", U:");
  Serial.print(map(i, 0, 1023, 0, 5000)/1000.0);
  Serial.println();
}