// Arduino 任务调度器 演示程序
// Created by Blanboom
// 2013.7.27
// https://blanboom.org

#include "TaskScheduler.h"  //包含此头文件，才能使用调度器

// 用于储存 LED 状态
boolean g_led1State=1;
boolean g_led2State=0;

void setup()
{
    // 第12、13脚接有 LED
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);

    Sch.init(); //初始化调度器

    //向调度器中添加任务
    //第一个参数为要添加任务的函数名
    //第二个参数为任务第一次执行的时间，
    //    合理设置有利于防止任务重叠，有利以提高任务执行的精度
    //第三个参数是任务执行的周期 只执行一次 0
    //第二、三个参数的单位均为毫秒，也可配置定时器修改其单位
    //第四个参数代表任务是合作式还是抢占式 1是合作、0是抢占
    //    一般取1就可以，更多用法请参考下文
    Sch.addTask(led1Update,0,1000,1);  //从第 0 毫秒开始闪烁 LED，每隔 1s, LED 状态改变一次
    Sch.addTask(led2Update,20,500,1);  //从第 20 毫秒开始闪烁 LED，每隔 0.5s, LED 状态改变一次

    Sch.start();//启动调度器
}

void loop()
{
    Sch.dispatchTasks();  // 执行被调度的任务，用调度器时放上这一句即可
}

// 把要调度的任务函数放下面

// 闪烁第 13 脚的 LED
void led1Update()
{
    if(g_led1State==0)
    {
        g_led1State=1;
        digitalWrite(13,HIGH);
    }
    else
    {
        g_led1State=0;
        digitalWrite(13,LOW);
    }
}

// 闪烁第 12 脚的 LED
void led2Update()
{
    if(g_led2State==0)
    {
        g_led2State=1;
        digitalWrite(12,HIGH);
    }
    else
    {
        g_led2State=0;
        digitalWrite(12,LOW);
    }
}