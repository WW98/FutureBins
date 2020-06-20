#include <Arduino.h>

const int trigPin_1 = 13;  //D13
const int echoPin_1 = 12;  //D12
const int trigPin_2 = 11;  //D11
const int echoPin_2 = 10;  //D10
const int trigPin_3 = 9;  //D9
const int echoPin_3 = 8;  //D8
const int trigPin_4 = 7;  //D7
const int echoPin_4 =6;  //D6
const int trigPin_5 = 5;  //D5
const int echoPin_5 = 4;  //D4
const int trigPin_none = 3;  //D3
const int echoPin_none = 2;  //D2

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

long Ultrasonic_none_duration; //None号垃圾箱时间计算
int Ultrasonic_none_distance;  //None号垃圾箱检测高度
int Overflow_none_state; //None号垃圾箱装载情况
int Overflow_none_number; //None号垃圾箱满载次数

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

  //初始化none号超声波传感器引脚
  pinMode(trigPin_none, OUTPUT);
  pinMode(echoPin_none, INPUT);

  Serial.begin(9600); //设置波特率
}

//定义各垃圾装载区的容量检测函数---------------------------------------------------------------------------------------------------------------------

//######################################################################################## 1

//定义1号超声波传感器—计算垃圾装载高度
int Ultrasonic_1()
{
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);
  Ultrasonic_1_duration = float(pulseIn(echoPin_1, HIGH));
  Ultrasonic_1_distance = Ultrasonic_1_duration / 58.00;

  Serial.print("Ultrasonic_1:");
  Serial.println(Ultrasonic_1_distance);
  return Ultrasonic_1_distance;
}

//定义1号超声波传感器—检测是否满溢
int Overflow_1()
{
  if (Ultrasonic_1() <= 10) {
    Overflow_1_state = 1;
  }
  else {
    Overflow_1_state = 0;
  }
  return Overflow_1_state;
}

//定义1号超声波传感器—统计满溢次数
int Overflow_1_add()
{
  if (Ultrasonic_1() <= 10) {
    Overflow_1_number = 1;
    return Overflow_1_number;
  }
}

//######################################################################################## 2

//定义2号超声波传感器—计算垃圾装载高度
int Ultrasonic_2()
{
  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
  Ultrasonic_2_duration = float(pulseIn(echoPin_2, HIGH));
  Ultrasonic_2_distance = Ultrasonic_2_duration / 58.00;

  Serial.print("Ultrasonic_2:");
  Serial.println(Ultrasonic_2_distance);
  return Ultrasonic_2_distance;
}

//定义2号超声波传感器—检测是否满溢
int Overflow_2()
{
  if (Ultrasonic_2() <= 10) {
    Overflow_2_state = 1;
  }
  else {
    Overflow_2_state = 0;
  }
  return Overflow_2_state;
}

//定义2号超声波传感器—统计满溢次数
int Overflow_2_add()
{
  if (Ultrasonic_2() <= 10) {
    Overflow_2_number = 1;
    return Overflow_2_number;
  }
}

//######################################################################################## 3

//定义3号超声波传感器—计算垃圾装载高度
int Ultrasonic_3()
{
  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);
  Ultrasonic_3_duration = float(pulseIn(echoPin_3, HIGH));
  Ultrasonic_3_distance = Ultrasonic_3_duration / 58.00;

  Serial.print("Ultrasonic_3:");
  Serial.println(Ultrasonic_3_distance);
  return Ultrasonic_3_distance;
}

//定义3号超声波传感器—检测是否满溢
int Overflow_3()
{
  if (Ultrasonic_3() <= 10) {
    Overflow_3_state = 1;
  }
  else {
    Overflow_3_state = 0;
  }
  return Overflow_3_state;
}

//定义3号超声波传感器—统计满溢次数
int Overflow_3_add()
{
  if (Ultrasonic_3() <= 10) {
    Overflow_3_number = 1;
    return Overflow_3_number;
  }
}

//######################################################################################## 4

//定义4号超声波传感器—计算垃圾装载高度
int Ultrasonic_4()
{
  digitalWrite(trigPin_4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_4, LOW);
  Ultrasonic_4_duration = float(pulseIn(echoPin_4, HIGH));
  Ultrasonic_4_distance = Ultrasonic_4_duration / 58.00;

  Serial.print("Ultrasonic_4:");
  Serial.println(Ultrasonic_4_distance);
  return Ultrasonic_4_distance;
}

//定义4号超声波传感器—检测是否满溢
int Overflow_4()
{
  if (Ultrasonic_4() <= 10) {
    Overflow_4_state = 1;
  }
  else {
    Overflow_4_state = 0;
  }
  return Overflow_4_state;
}

//定义4号超声波传感器—统计满溢次数
int Overflow_4_add()
{
  if (Ultrasonic_4() <= 10) {
    Overflow_4_number = 1;
    return Overflow_4_number;
  }
}

//######################################################################################## 5

//定义5号超声波传感器—计算垃圾装载高度
int Ultrasonic_5()
{
  digitalWrite(trigPin_5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_5, LOW);
  Ultrasonic_5_duration = float(pulseIn(echoPin_5, HIGH));
  Ultrasonic_5_distance = Ultrasonic_5_duration / 58.00;

  Serial.print("Ultrasonic_5:");
  Serial.println(Ultrasonic_5_distance);
  return Ultrasonic_5_distance;
}

//定义5号超声波传感器—检测是否满溢
int Overflow_5()
{
  if (Ultrasonic_5() <= 10) {
    Overflow_5_state = 1;
  }
  else {
    Overflow_5_state = 0;
  }
  return Overflow_5_state;
}

//定义5号超声波传感器—统计满溢次数
int Overflow_5_add()
{
  if (Ultrasonic_5() <= 10) {
    Overflow_5_number = 1;
    return Overflow_5_number;
  }
}

//######################################################################################## None

//定义None超声波传感器—计算垃圾装载高度
int Ultrasonic_none()
{
  digitalWrite(trigPin_none, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_none, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_none, LOW);
  Ultrasonic_none_duration = float(pulseIn(echoPin_none, HIGH));
  Ultrasonic_none_distance = Ultrasonic_none_duration / 58.00;

  Serial.print("Ultrasonic_none:");
  Serial.println(Ultrasonic_none_distance);
  return Ultrasonic_none_distance;
}

//定义None号超声波传感器—检测是否满溢
int Overflow_none()
{
  if (Ultrasonic_none() <= 10) {
    Overflow_none_state = 1;
  }
  else {
    Overflow_none_state = 0;
  }
  return Overflow_none_state;
}

//定义None号超声波传感器—统计满溢次数
int Overflow_none_add()
{
  if (Ultrasonic_none() <= 10) {
    Overflow_none_number = 1;
    return Overflow_none_number;
  }
}

void loop()
{
  Serial.println("Please Waiting...");
  Ultrasonic_1();
  Ultrasonic_2();
  Ultrasonic_3();
  Ultrasonic_4();
  Ultrasonic_5();
  Ultrasonic_none();
  Serial.println("End...");
  Serial.println();
}

