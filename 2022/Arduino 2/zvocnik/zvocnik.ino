#define ZVOCNIK A5

#define TONE_A1 440

#define TONE_C1 261
#define TONE_D 293
#define TONE_E 329
#define TONE_F 349
#define TONE_G 392
#define TONE_A 440
#define TONE_H 493
#define TONE_C2 523

char tipke[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i'};
int toni[] = {TONE_C1, TONE_D, TONE_E, TONE_F, TONE_G, TONE_A, TONE_H, TONE_C2};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(ZVOCNIK, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char c = Serial.read();

    for (int i = 0; i < 8; i++) {
      if (tipke[i] == c) {
        tone(ZVOCNIK, toni[i], 500);
        delay(600);
      }
    }
  }
}