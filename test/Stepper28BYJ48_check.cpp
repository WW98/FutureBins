#include <AccelStepper.h>
 
// 电机步进方式定义
#define FULLSTEP 4    //全步进参数
#define HALFSTEP 8    //半步进参数
 
//投放口控制电机
#define BYJ48_0_In1 22 //28BYJ48_In1引脚定义
#define BYJ48_0_In2 24 //28BYJ48_In2引脚定义
#define BYJ48_0_In3 26 //28BYJ48_In3引脚定义
#define BYJ48_0_In4 28 //28BYJ48_In4引脚定义

//第一层分类控制电机
#define BYJ48_1_In1 23 //28BYJ48_In1引脚定义
#define BYJ48_1_In2 25 //28BYJ48_In2引脚定义
#define BYJ48_1_In3 27 //28BYJ48_In3引脚定义
#define BYJ48_1_In4 29 //28BYJ48_In4引脚定义

//第二层分类控制电机
#define BYJ48_2_In1 31 //28BYJ48_In1引脚定义
#define BYJ48_2_In2 33 //28BYJ48_In2引脚定义
#define BYJ48_2_In3 35 //28BYJ48_In3引脚定义
#define BYJ48_2_In4 37 //28BYJ48_In4引脚定义
 
// 定义三个步进电机对象
AccelStepper stepper1(FULLSTEP, BYJ48_0_In1, BYJ48_0_In3, BYJ48_0_In2, BYJ48_0_In4);
AccelStepper stepper2(FULLSTEP, BYJ48_1_In1, BYJ48_1_In3, BYJ48_1_In2, BYJ48_1_In4);
AccelStepper stepper3(FULLSTEP, BYJ48_2_In1, BYJ48_2_In3, BYJ48_2_In2, BYJ48_2_In4);
 
char Bins_state;

void setup() {
  stepper1.setMaxSpeed(500.0);    // 1号电机最大速度500 
  stepper1.setAcceleration(50.0);  // 1号电机加速度50.0
 
  stepper2.setMaxSpeed(500.0);    // 2号电机最大速度500 
  stepper2.setAcceleration(50.0);  // 2号电机加速度50.0

  stepper3.setMaxSpeed(500.0);    // 3号电机最大速度500 
  stepper3.setAcceleration(50.0);  // 3号电机加速度50.0
}
 
void loop() {
  if (Serial.available() > 0)
  {
    Bins_state = Serial.read();
    if(Bins_state == 'k'){
          if ( stepper1.currentPosition() == 0 && stepper2.currentPosition() == 0 && stepper3.currentPosition() == 0 ){
    // 电机转动半周
    stepper1.moveTo(2048);              
    stepper2.moveTo(2048);
    stepper3.moveTo(2048);  
    
  } else if ( stepper1.currentPosition() == 2048 && stepper2.currentPosition() == 2048 && stepper3.currentPosition() == 2048){
    // 电机转动半周
    stepper1.moveTo(0);            
    stepper2.moveTo(0); 
    stepper3.moveTo(0);  
  }  
    }
   
  }
  stepper1.run();   // 1号电机运行
  stepper2.run();   // 2号电机运行
  stepper3.run();   // 3号电机运行
}