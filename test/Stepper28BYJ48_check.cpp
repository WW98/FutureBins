#include <Stepper28BYJ48.h>
#include <Arduino.h>
const int stepsPerRevolution = 1024;  //28BYJ48电机旋转90°需要的步数

// 电机接在引脚A12,A13,A14,A15
Stepper myStepper(stepsPerRevolution, 69, 68, 67, 66);

int stepCount = 0;         // number of steps the motor has taken

void setup(){

  Serial.begin(9600);
  myStepper.setSpeed(16);

}

void loop(){
  //正转90°
  myStepper.step(stepsPerRevolution);
  Serial.print("steps:" );
  Serial.println(stepsPerRevolution);
  delay(5000);

  //反转90°
  myStepper.step(-stepsPerRevolution);
  Serial.print("steps:" );
  Serial.println(-stepsPerRevolution);
  delay(5000);

}