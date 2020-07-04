#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {

    if('s' == Serial.read())
      {
        Serial.println("Received successfully !");
      }
  }
}
