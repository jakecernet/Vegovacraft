#include <DHT.h>
#include <Servo.h>

#define servo_pin 3
#define dht_pin 4

Servo mojservo;

DHT dht = DHT(dht_pin, DHT11);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  dht.begin();
  mojservo.attach(servo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(dht.readHumidity());
  //Serial.print("  ");
  //Serial.println(dht.readTemperature());  
  //delay(100);

  float temperatura = 30;

  int servo_kot = map(temperatura, 15, 30, 0, 180);

  mojservo.write(servo_kot);

}
