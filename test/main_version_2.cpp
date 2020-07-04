#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Stepper28BYJ48.h>
#include <Syn6288.h>
#include <AccelStepper.h>

//温度传感器
#define ONE_WIRE_BUS 14 //DS18B20引脚定义

//超声波传感器一号
#define trigPin_1 13 //ultrasonic_1_trig引脚定义
#define echoPin_1 12 //ultrasonic_1_echo引脚定义

//超声波传感器二号
#define trigPin_2 11 //ultrasonic_2_trig引脚定义
#define echoPin_2 10 //ultrasonic_2_echo引脚定义

//超声波传感器三号
#define trigPin_3 9 //ultrasonic_3_trig引脚定义
#define echoPin_3 8 //ultrasonic_3_echo引脚定义

//超声波传感器四号
#define trigPin_4 7  //ultrasonic_4_trig引脚定义
#define echoPin_4 6  //ultrasonic_4_echo引脚定义

//超声波传感器五号
#define trigPin_5 5  //ultrasonic_5_trig引脚定义
#define echoPin_5 4 //ultrasonic_5_echo引脚定义

//直流电机风扇
#define motorIn3 57 //DC_FAN_In3引脚定义
#define motorIn4 58 //DC_FAN_In4引脚定义

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

const int stepCount = 0;  //电动机已采取的步数
const int rank1 = 150;//风扇强度档次变量150
const int rank2 = 200; //风扇强度档次变量200
const int rank3 = 250;//风扇强度档次变量250
const int stepsPerRevolution = 4096;  //28BYJ48电机旋转一周需要的步数

long tem_value; //温度数值
long Ultrasonic_1_duration; //1号垃圾箱时间计算
int Ultrasonic_1_distance;  //1号垃圾箱检测高度
int Overflow_1_state; //1号垃圾箱装载情况
int Overflow_1_number; //1号垃圾箱满载次数
long Ultrasonic_2_duration; //2号垃圾箱时间计算
int Ultrasonic_2_distance;  //2号垃圾箱检测高度
int Overflow_2_state; //2号垃圾箱装载情况
int Overflow_2_number; //2号垃圾箱满载次数
long Ultrasonic_3_duration; //3号垃圾箱时间计算
int Ultrasonic_3_distance;  //3号垃圾箱检测高度
int Overflow_3_state; //3号垃圾箱装载情况
int Overflow_3_number; //3号垃圾箱满载次数
long Ultrasonic_4_duration; //4号垃圾箱时间计算
int Ultrasonic_4_distance;  //4号垃圾箱检测高度
int Overflow_4_state; //4号垃圾箱装载情况
int Overflow_4_number; //4号垃圾箱满载次数
long Ultrasonic_5_duration; //5号垃圾箱时间计算
int Ultrasonic_5_distance;  //5号垃圾箱检测高度
int Overflow_5_state; //5号垃圾箱装载情况
int Overflow_5_number; //5号垃圾箱满载次数

unsigned char Bins_state; //垃圾类型识别结果

OneWire oneWire(ONE_WIRE_BUS);  //设置oneWire实例以与任何oneWire设备通信
DallasTemperature sensors(&oneWire);  //把温度传给oneWire
AccelStepper stepper1(FULLSTEP, BYJ48_0_In1, BYJ48_0_In3, BYJ48_0_In2, BYJ48_0_In4);  //实例化28BYJ48对象:投放口控制
AccelStepper stepper2(FULLSTEP, BYJ48_1_In1, BYJ48_1_In3, BYJ48_1_In2, BYJ48_1_In4);  //实例化28BYJ48对象:第一层分流盖
AccelStepper stepper3(FULLSTEP, BYJ48_2_In1, BYJ48_2_In3, BYJ48_2_In2, BYJ48_2_In4);  //实例化28BYJ48对象:第二层分流盖
Syn6288 syn;  //实例化syn6288对象

uint8_t text1[] = {0xBF, 0xC9, 0xBB, 0xD8, 0xCA, 0xD5, 0xC0, 0xAC, 0xBB, 0xF8}; //播音文本：可回收垃圾
uint8_t text2[] = {0xD3, 0xD0, 0xB6, 0xBE, 0xD3, 0xD0, 0xBA, 0xA6, 0xC0, 0xAC, 0xBB, 0xF8}; //播音文本：有毒有害垃圾
uint8_t text3[] = {0xB3, 0xF8, 0xD3, 0xE0, 0xBB, 0xF2, 0xCA, 0xAA, 0xC0, 0xAC, 0xBB, 0xF8}; //播音文本：厨余或湿垃圾
uint8_t text4[] = {0xB8, 0xC9, 0xC0, 0xAC, 0xBB, 0xF8}; //播音文本：干垃圾
uint8_t text5[] = {0xC6, 0xE4, 0xCB, 0xFB, 0xC0, 0xAC, 0xBB, 0xF8}; //播音文本：其他垃圾
uint8_t text6[] = {0xB8, 0xC3, 0xC0, 0xAC, 0xBB, 0xF8, 0xCB, 0xF9, 0xCA, 0xF4, 0xD7, 0xB0, 0xD4, 0xD8, 0xC7, 0xF8, 0xD2, 0xD1, 0xC2, 0xFA}; //该垃圾所属装载区已满

//定义温度传感器函数
long Tem_upload()
{
  sensors.requestTemperatures();
  tem_value = (sensors.getTempCByIndex(0));
  //Serial.print("Tem: ");
  //Serial.print(tem_value);
  //Serial.println(" C");
  //Serial.print("Tem: ");
  //Serial.print(1.8*sensors.getTempCByIndex(0) + 32.0);
  //Serial.println(" F");
  return tem_value;
}

//定义直流电机风扇函数
void FAN(int num_FAN)
{
  switch (num_FAN)
  {
  case 0:
      {
        analogWrite(motorIn3,0);
        analogWrite(motorIn4,0);
      }
    break;
  case 1:
      {
        analogWrite(motorIn3,0);
        analogWrite(motorIn4,rank3);
      }
  default:
    break;
  }
}

//定义一号垃圾装载区的容量检测函数:"1"计算垃圾装载高度,"2"检测是否满溢,"3"统计满溢次数
int Bin_1(int bin_1_num)
{
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);
  Ultrasonic_1_duration = float(pulseIn(echoPin_1, HIGH));
  Ultrasonic_1_distance = Ultrasonic_1_duration / 58.00;

  if (Ultrasonic_1_distance <= 10) {
    Overflow_1_state = 1;
  }
  else {
    Overflow_1_state = 0;
  }

  if (Ultrasonic_1_distance <= 10) {
    Overflow_1_number = 1;
  }

  switch (bin_1_num)
  {
  case 1:
    {
      //Serial.print("Bin_1_distance:");
      //Serial.println(Ultrasonic_1_distance);
      return Ultrasonic_1_distance;
    }
    break;
  case 2:
    {
      //Serial.print("Bin_1_OverflowState:");
      //Serial.println(Overflow_1_state);
      return Overflow_1_state;
    }
    break;
  case 3:
    {
      //Serial.print("Bin_1_OverflowCount:");
      //Serial.println(Overflow_1_number);
      return Overflow_1_number;
    }
    break;
  default:
    break;
  }
}

//定义二号垃圾装载区的容量检测函数:"1"计算垃圾装载高度,"2"检测是否满溢,"3"统计满溢次数
int Bin_2(int bin_2_num)
{
  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
  Ultrasonic_2_duration = float(pulseIn(echoPin_2, HIGH));
  Ultrasonic_2_distance = Ultrasonic_2_duration / 58.00;

  if (Ultrasonic_2_distance <= 10) {
    Overflow_2_state = 1;
  }
  else {
    Overflow_2_state = 0;
  }

  if (Ultrasonic_2_distance <= 10) {
    Overflow_2_number = 1;
  }
  
  switch(bin_2_num)
  {
  case 1:
    {
      //Serial.print("Bin_2_distance:");
      //Serial.println(Ultrasonic_2_distance);
      return Ultrasonic_2_distance;
    }
    break;
  case 2:
    {
      //Serial.print("Bin_2_OverflowState:");
      //Serial.println(Overflow_2_state);
      return Overflow_2_state;
    }
    break;
  case 3:
    {
      //Serial.print("Bin_2_OverflowCount:");
      //Serial.println(Overflow_2_number);
      return Overflow_2_number;
    }
    break;
  default:
    break;
  }
}

//定义三号垃圾装载区的容量检测函数:"1"计算垃圾装载高度,"2"检测是否满溢,"3"统计满溢次数
int Bin_3(int bin_3_num)
{
  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);
  Ultrasonic_3_duration = float(pulseIn(echoPin_3, HIGH));
  Ultrasonic_3_distance = Ultrasonic_3_duration / 58.00;

  if (Ultrasonic_3_distance <= 10) {
    Overflow_3_state = 1;
  }
  else {
    Overflow_3_state = 0;
  }

  if (Ultrasonic_3_distance <= 10) {
    Overflow_3_number = 1;
  }
  
  switch(bin_3_num)
  {
  case 1:
    {
      //Serial.print("Bin_3_distance:");
      //Serial.println(Ultrasonic_3_distance);
      return Ultrasonic_3_distance;
    }
    break;
  case 2:
    {
      //Serial.print("Bin_3_OverflowState:");
      //Serial.println(Overflow_3_state);
      return Overflow_3_state;
    }
    break;
  case 3:
    {
      //Serial.print("Bin_3_OverflowCount:");
      //Serial.println(Overflow_3_number);
      return Overflow_3_number;
    }
    break;
  default:
    break;
  }
}

//定义四号垃圾装载区的容量检测函数:"1"计算垃圾装载高度,"2"检测是否满溢,"3"统计满溢次数
int Bin_4(int bin_4_num)
{
  digitalWrite(trigPin_4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_4, LOW);
  Ultrasonic_4_duration = float(pulseIn(echoPin_4, HIGH));
  Ultrasonic_4_distance = Ultrasonic_4_duration / 58.00;

  if (Ultrasonic_4_distance <= 10) {
    Overflow_4_state = 1;
  }
  else {
    Overflow_4_state = 0;
  }

  if (Ultrasonic_4_distance <= 10) {
    Overflow_4_number = 1;
  }
  
  switch(bin_4_num)
  {
  case 1:
    {
      //Serial.print("Bin_4_distance:");
      //Serial.println(Ultrasonic_4_distance);
      return Ultrasonic_4_distance;
    }
    break;
  case 2:
    {
      //Serial.print("Bin_4_OverflowState:");
      //Serial.println(Overflow_4_state);
      return Overflow_4_state;
    }
    break;
  case 3:
    {
      //Serial.print("Bin_4_OverflowCount:");
      //Serial.println(Overflow_4_number);
      return Overflow_4_number;
    }
    break;
  default:
    break;
  }
}

//定义五号垃圾装载区的容量检测函数:"1"计算垃圾装载高度,"2"检测是否满溢,"3"统计满溢次数
int Bin_5(int bin_5_num)
{
  digitalWrite(trigPin_5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_5, LOW);
  Ultrasonic_5_duration = float(pulseIn(echoPin_5, HIGH));
  Ultrasonic_5_distance = Ultrasonic_5_duration / 58.00;

  if (Ultrasonic_5_distance <= 10) {
    Overflow_5_state = 1;
  }
  else {
    Overflow_5_state = 0;
  }

  if (Ultrasonic_5_distance <= 10) {
    Overflow_5_number = 1;
  }
  
  switch(bin_5_num)
  {
  case 1:
    {
      //Serial.print("Bin_5_distance:");
      //Serial.println(Ultrasonic_5_distance);
      return Ultrasonic_5_distance;
    }
    break;
  case 2:
    {
      //Serial.print("Bin_5_OverflowState:");
      //Serial.println(Overflow_5_state);
      return Overflow_5_state;
    }
    break;
  case 3:
    {
      //Serial.print("Bin_5_OverflowCount:");
      //Serial.println(Overflow_5_number);
      return Overflow_5_number;
    }
    break;
  default:
    break;
  }
}

//定义语音播放模块函数：“1”可回收垃圾，“2”有毒有害垃圾，“3”厨余或湿垃圾，“4”干垃圾，“5”其他垃圾
void voice(int num_voice)
{
  switch (num_voice)
  {
  case 1:
    syn.play(text1, sizeof(text1), 1);
    break;
  case 2:
    syn.play(text1, sizeof(text2), 2);
    break;
  case 3:
    syn.play(text1, sizeof(text3), 3);
    break;
  case 4:
    syn.play(text1, sizeof(text4), 4);
    break;
  case 5:
    syn.play(text1, sizeof(text5), 5);
    break;
  case 6:
    syn.play(text6, sizeof(text6), 6);
  default:
    break;
  }
}

//定义等待投放的时间
void waiting(int timesNum)
{
    delay(timesNum * 1000);
}
//系统操作：可回收垃圾类型
void Garbage_disposal_1()
{
    stepper2.moveTo(0);
    stepper3.moveTo(512); 
    stepper1.runToNewPosition(1024);
    voice(1);
    waiting(5);
    stepper1.runToNewPosition(0);
    stepper2.moveTo(0);
    stepper3.moveTo(0); 

    stepper1.run();   // 1号电机运行
    stepper2.run();   // 2号电机运行
    stepper3.run();   // 3号电机运行
}

//系统操作：厨余或湿垃圾类型
void Garbage_disposal_2()
{
    stepper2.moveTo(0);
    stepper3.moveTo(1024); 
    stepper1.runToNewPosition(1024);
    voice(3);
    waiting(5);
    stepper1.runToNewPosition(0);
    stepper2.moveTo(0);
    stepper3.moveTo(0); 

    stepper1.run();   // 1号电机运行
    stepper2.run();   // 2号电机运行
    stepper3.run();   // 3号电机运行
}

//系统操作：有毒垃圾类型
void Garbage_disposal_3()
{
    stepper2.moveTo(0);
    stepper3.moveTo(1536); 
    stepper1.runToNewPosition(1024);
    voice(2);
    waiting(5);
    stepper1.runToNewPosition(0);
    stepper2.moveTo(0);
    stepper3.moveTo(0); 

    stepper1.run();   // 1号电机运行
    stepper2.run();   // 2号电机运行
    stepper3.run();   // 3号电机运行
}

//系统操作：干垃圾类型
void Garbage_disposal_4()
{
    stepper2.moveTo(0);
    stepper3.moveTo(2048); 
    stepper1.runToNewPosition(1024);
    voice(4);
    waiting(5);
    stepper1.runToNewPosition(0);
    stepper2.moveTo(0);
    stepper3.moveTo(0); 

    stepper1.run();   // 1号电机运行
    stepper2.run();   // 2号电机运行
    stepper3.run();   // 3号电机运行
}

//系统操作：其它类型
void Garbage_disposal_5()
{
    stepper2.moveTo(1024);
    stepper3.moveTo(0);
    stepper1.runToNewPosition(1024);
    voice(5);
    waiting(5);
    stepper1.runToNewPosition(0);
    stepper2.moveTo(0);
    stepper3.moveTo(0);

    stepper1.run();   // 1号电机运行
    stepper2.run();   // 2号电机运行
    stepper3.run();   // 3号电机运行 
}


void setup()
{
  //初始化1号超声波传感器引脚
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);

  //初始化2号超声波传感器引脚
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);

  //初始化3号超声波传感器引脚
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);

  //初始化4号超声波传感器引脚
  pinMode(trigPin_4, OUTPUT);
  pinMode(echoPin_4, INPUT);

  //初始化5号超声波传感器引脚
  pinMode(trigPin_5, OUTPUT);
  pinMode(echoPin_5, INPUT);

  //初始化风扇引脚
  pinMode(motorIn3,OUTPUT);
  pinMode(motorIn4,OUTPUT);

  //初始化DS18B20
  sensors.begin();

  stepper1.setMaxSpeed(500.0);    // 1号电机最大速度500 
  stepper1.setAcceleration(50.0);  // 1号电机加速度50.0
 
  stepper2.setMaxSpeed(500.0);    // 2号电机最大速度500 
  stepper2.setAcceleration(50.0);  // 2号电机加速度50.0

  stepper3.setMaxSpeed(500.0);    // 2号电机最大速度500 
  stepper3.setAcceleration(50.0);  // 2号电机加速度50.0
  
  //设置串口波特率
  Serial.begin(9600);
}

void loop()
{
      //判断串口缓存区有没有数据
  if(Serial.available())
  {
    //有数据就用read来读取并赋值
    Bins_state = Serial.read();

    //垃圾类型判断
    switch (Bins_state)
    {
    case 'k':
      {
        if(Bin_1(2) == 0){
            Garbage_disposal_1();
        }
        else
        {
          voice(6); //播放语音：该垃圾所属装载区已满
        } 
      }
      break;
    case 'c':
      {
        if(Bin_2(2) == 0){
            Garbage_disposal_2();
        }
        else
        {
          voice(6); //播放语音：该垃圾所属装载区已满
        } 
      }
      break;
    case 'y':
      {
        if(Bin_3(2) == 0){
            Garbage_disposal_3();
        }
        else
        {
          voice(6); //播放语音：该垃圾所属装载区已满
        } 
      }
      break;
    case 'g':
      {
        if(Bin_4(2) == 0){
            Garbage_disposal_4();
        }
        else
        {
          voice(6); //播放语音：该垃圾所属装载区已满
        } 
      }
      break;
    case 'q':
      {
        if(Bin_5(2) == 0){
            Garbage_disposal_5();
        }
        else
        {
          voice(6); //播放语音：该垃圾所属装载区已满
        } 
      }
      break;
    default:
      break;
    }
    
    //给树莓派返回接收成功的消息
    Serial.println("Received successfully !");
  
  }


  } 
}
