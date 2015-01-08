#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// found program to get this device address
DeviceAddress insideThermometer = { 0x28, 0x6E, 0x32, 0x2B, 0x06, 0x00, 0x00, 0xFC };
const int relayPin1 = 8;
 float tempF;
 boolean Cold = true;

void setup(void)
{
  pinMode(relayPin1, OUTPUT);      
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(insideThermometer, 10);
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print(" F: ");
    tempF = DallasTemperature::toFahrenheit(tempC);
    Serial.print(tempF);
  }
}

void loop(void)
{ 
  delay(500);
  sensors.requestTemperatures();
  printTemperature(insideThermometer);
  Serial.print("\n\r");
  checkTemp();
}

void checkTemp(void)
{
  if (!Cold && tempF < 75) { Cold = true; digitalWrite(relayPin1, LOW); }
  if (Cold && tempF > 80) {Cold =false; digitalWrite(relayPin1, HIGH);}
} 

