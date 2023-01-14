#include <Arduino.h>

#define LED_red 6
#define LED_green 5
#define servo 3

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_green, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(servo, OUTPUT);
  Serial.begin(9600);

}

int del = 5;
int pot = 0;

void loop() {
  // put your main code here, to run repeatedly:
  
  pot = (analogRead(A0))/4;

  //digitalWrite(LED_green, 1);
  //digitalWrite(LED_red, 1);
  //delayMicroseconds(pot);
  //digitalWrite(LED_green, 0);
  //digitalWrite(LED_red, 0);
  //delayMicroseconds(1023-pot);
  
  Serial.println(pot);

  analogWrite(LED_green, pot);
  analogWrite(LED_red, 255-pot);
  analogWrite(servo, pot);
  

}
