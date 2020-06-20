#include <Arduino.h>
const int avoidPin = 56;  
unsigned long starttime;
unsigned long stoptime;
unsigned long looptime;

void setup()
{
  pinMode(avoidPin, INPUT);  //set the avoidPin as INPUT
  Serial.begin(9600);
}

void loop()
{
  boolean avoidVal = digitalRead(avoidPin);  

  while(avoidVal == LOW) 
  {
    starttime = millis();
    Serial.println("正在识别您是否需要丢垃圾：停留超过两秒再离开即为选择丢垃圾，否则不是！");
    
    while(1){
      boolean avoidVal_end = digitalRead(avoidPin); 
      if(avoidVal_end == HIGH){
          stoptime = millis();
          break;
      }
    }
    
    looptime = stoptime - starttime;
    if(looptime >= 1000){
      Serial.println("已确认您需要丢垃圾！");
      //return 1;
      break;
      }
    else{
      Serial.println("已确认您不需要丢垃圾！");
      //return 1;
      break;
      }
   } 
}
