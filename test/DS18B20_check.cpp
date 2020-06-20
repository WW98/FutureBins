#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#define ONE_WIRE_BUS 14 //ds18b20 module attach to D14
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{

  // start serial port
  Serial.begin(9600);
  sensors.begin(); // initialize the bus
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures

  Serial.print("Tem: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" C");

  //Serial.print("Tem: ");
  //Serial.print(1.8*sensors.getTempCByIndex(0) + 32.0);
  //Serial.println(" F");
}