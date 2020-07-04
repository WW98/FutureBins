#include <Arduino.h>
#include <Servo.h>

Servo servo_one;
Servo servo_two;

int onePin = 54;
int twoPin = 55;

void loop() {
  servo_one.write(90);
  servo_two.write(90);
  delay(1000);
  
  servo_one.write(0);
  servo_two.write(0);
  delay(1000);
}