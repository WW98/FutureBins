#include <Arduino.h>
const int motorIn3 = 57;
const int motorIn4 = 58;

#define rank1 150
#define rank2 200
#define rank3 250

void setup() 
{
  pinMode(motorIn3,OUTPUT);
  pinMode(motorIn4,OUTPUT);
  Serial.begin(9600);
}

void clockwise(int Speed)//
{
  analogWrite(motorIn3,0);
  analogWrite(motorIn4,Speed);
}

void loop() {
 
  //clockwise(rank1);//set the rotate speed of the motor as rank1=150
  //clockwise(rank2);//set the rotate speed of the motor as rank1=200
  clockwise(rank3);//set the rotate speed of the motor as rank1=250

}
