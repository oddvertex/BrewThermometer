#include <TaskManager.h>
#include <Time.h>
#include <LiquidCrystal.h>
// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer = { 0x28, 0xCA, 0x4D, 0x2B, 0x06, 0x00, 0x00, 0x7E };
DeviceAddress outsideThermometer = { 0x28, 0x6B, 0x24, 0x2C, 0x06, 0x00, 0x00, 0x71 };
// get address of thermometer by running 


LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);


void setup()
{
  // Initialize lcd
  lcd.begin(20,4);              // rows , columns
  int backLight = 9;            // pin 9 will control the backlight
  pinMode(backLight, OUTPUT);   // backlight on pin 9, green jumper
  digitalWrite(backLight,LOW);  // start dark
  lcd.clear();                  // start empty
               
  // Initialize Thermometer
  sensors.setResolution(insideThermometer, 10); // 9 to 12 bits
  sensors.setResolution(outsideThermometer, 10); // 9 to 12 bits
  sensors.begin();
  
  lcd.setCursor(0,0);
  lcd.print("    Bradshaw Beer");

  for (int j=1; j<200; j+=1){
    analogWrite(backLight, j);   // fade backlight in PWM
    delay(10);
  }
  delay(1);
  digitalWrite(backLight,HIGH);

  lcd.setCursor(0,0);               // set cursor to column 0, row 0 (the first row)
  lcd.print("                    ");  // change this text to whatever you like. keep it clean.
  lcd.setCursor(0,1);               // set cursor to column 0, row 1
  lcd.print("=--noTemp");
  lcd.setCursor(11,1); 
  lcd.print("=--noTemp");
  //lcd.setCursor(0,2);
  //lcd.print("Tc=noTemp");
  //lcd.setCursor(11,2);
  //lcd.print("Td=noTemp");
  //lcd.setCursor(0,3);         
  //lcd.print("H: 60_ 15_ 2_");
  
 TaskMgr.add(1,looper);
 TaskMgr.add(2,printTime);
}

void looper()
{
  //delay(200);
  sensors.requestTemperatures();
  
  lcd.setCursor(3,1);
  printTemperature(insideThermometer);
  lcd.setCursor(8,1);
  lcd.print(" ");
  lcd.setCursor(14,1);
  printTemperature(outsideThermometer);
  lcd.setCursor(19,1);
  lcd.print(" ");
  lcd.setCursor(0,3);
  
}
void printTime() {
if ((59-minute())<10) {lcd.print("0");}
  lcd.print(59-minute());
  lcd.print(":");
  if ((59-second())<10) {lcd.print("0");}
  lcd.print(59-second());
}
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    lcd.print("Error.");
  } 
  else {
    //lcd.setCursor(3,1);
    float tempF = DallasTemperature::toFahrenheit(tempC);
    //tempF = .1*int(10*tempF);
    lcd.print(tempF);
    lcd.print(" ");
  }
}
/* ------------------------------------------------------------------------------- */


