#define JOY_X A5
#define JOY_Y A4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int joy_x = analogRead(JOY_X);
  int joy_y = analogRead(JOY_Y);
  Serial.print(joy_x);
  Serial.print(", ");
  Serial.println(joy_y);
}
