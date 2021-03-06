#include <Arduino.h>
#include <Syn6288.h>
Syn6288 syn;

uint8_t text1[] = {0xBF, 0xC9, 0xBB, 0xD8, 0xCA, 0xD5, 0xC0, 0xAC, 0xBB, 0xF8}; //可回收垃圾
uint8_t text2[] = {0xD3, 0xD0, 0xB6, 0xBE, 0xD3, 0xD0, 0xBA, 0xA6, 0xC0, 0xAC, 0xBB, 0xF8}; //有毒有害垃圾
uint8_t text3[] = {0xB3, 0xF8, 0xD3, 0xE0, 0xBB, 0xF2, 0xCA, 0xAA, 0xC0, 0xAC, 0xBB, 0xF8}; //厨余或湿垃圾
uint8_t text4[] = {0xB8, 0xC9, 0xC0, 0xAC, 0xBB, 0xF8}; //干垃圾
uint8_t text5[] = {0xC6, 0xE4, 0xCB, 0xFB, 0xC0, 0xAC, 0xBB, 0xF8}; //其他垃圾
uint8_t text6[] = {0xB8, 0xC3, 0xC0, 0xAC, 0xBB, 0xF8, 0xCB, 0xF9, 0xCA, 0xF4, 0xD7, 0xB0, 0xD4, 0xD8, 0xC7, 0xF8, 0xD2, 0xD1, 0xC2, 0xFA}; //该垃圾所属装载区已满

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  syn.play(text1, sizeof(text1), 1);
  syn.play(text2, sizeof(text2), 2);
  syn.play(text3, sizeof(text3), 3);
  syn.play(text4, sizeof(text4), 4);
  syn.play(text5, sizeof(text5), 5);
  syn.play(text6, sizeof(text6), 6);
}