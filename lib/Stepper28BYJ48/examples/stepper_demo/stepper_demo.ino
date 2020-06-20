
/*
	控制28BYJ48电机，正转一圈，反转一圈
 */

#include <Stepper28BYJ48.h>

const int stepsPerRevolution = 4096;  //28BYJ48电机旋转一周需要的步数


// 电机接在引脚8 ~ 11: 电机线依次为蓝，粉，黄，橙
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;         // number of steps the motor has taken

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  
  //设置电机转速r/min
  myStepper.setSpeed(10);
}

void loop() {
  // 正转一圈
  myStepper.step(stepsPerRevolution);
  Serial.print("steps:" );
  Serial.println(stepsPerRevolution);
  delay(5000);
  
  // 反转一圈
  myStepper.step(-stepsPerRevolution);
  Serial.print("steps:" );
  Serial.println(-stepsPerRevolution);
  delay(5000);
  
  // 正转64步
  myStepper.step(64);
  Serial.print("steps:" );
  Serial.println(64);
  delay(5000);
  
  // 正转64步
  myStepper.step(64);
  Serial.print("steps:" );
  Serial.println(64);
  delay(5000);
  
}

