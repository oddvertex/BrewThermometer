#include <TaskManager.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermOne = { };
DeviceAddress thermTwo = { };
DeviceAddress thermThree = { };
DeviceAddress thermFour = { };
int thermCount = 0;
  
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
    
  while(oneWire.search(addr)) {
    switch (thermCount) {
    case 0: for( i = 0; i < 8; i++) { thermOne[i] = addr[i];}
    case 1: for( i = 0; i < 8; i++) { thermTwo[i] = addr[i];}
    case 2: for( i = 0; i < 8; i++) { thermThree[i] = addr[i];}
    case 3: for( i = 0; i < 8; i++) { thermFour[i] = addr[i];}
    }
    thermCount+=1;
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        //return;
    }
  } 
  
  oneWire.reset_search();
  
  lcd.begin(20,4);              // rows , columns
  int backLight = 9;            // pin 9 will control the backlight
  pinMode(backLight, OUTPUT);   // backlight on pin 9, green jumper
  digitalWrite(backLight,LOW);  // start dark
  lcd.clear();                  // start empty
               
  // Initialize Thermometer
  sensors.setResolution(thermOne, 10);   // 9 to 12 bits
  sensors.setResolution(thermTwo, 10);   // 9 to 12 bits
  sensors.setResolution(thermThree, 10); // 9 to 12 bits
  sensors.setResolution(thermFour, 10);  // 9 to 12 bits
  
  sensors.begin();
  
  lcd.setCursor(0,0);
  lcd.print("    Bradshaw Beer");

  for (int j=1; j<255; j+=1){
    analogWrite(backLight, j);   // fade backlight in PWM
    delay(10);
  }
  digitalWrite(backLight,HIGH);

  lcd.setCursor(0,0);               // set cursor to column 0, row 0 (the first row)
  lcd.print("                    ");  // change this text to whatever you like. keep it clean.
  
  if (thermCount>0) {
    lcd.setCursor(0,1);               // set cursor to column 0, row 1
    lcd.print("=--noTemp");
  }
  if (thermCount>1) {
    lcd.setCursor(11,1); 
    lcd.print("=--noTemp");
  }
  if (thermCount>2) {
    lcd.setCursor(0,2);
    lcd.print("=--noTemp");
  }
  if (thermCount>3) {
    lcd.setCursor(11,2);
    lcd.print("=--noTemp");
  }
 TaskMgr.add(1,looper);
 //TaskMgr.add(2,printTime);
}

void looper()
{
  sensors.requestTemperatures();
  
  if (thermCount>0) {
    lcd.setCursor(3,1);
    printTemperature(thermOne);
    lcd.setCursor(8,1);
    lcd.print(" ");
  }
  if (thermCount>1) {
    lcd.setCursor(14,1);
    printTemperature(thermTwo);
    lcd.setCursor(19,1);
    lcd.print(" ");
  }
  if (thermCount>2) {
    lcd.setCursor(3,2);
    printTemperature(thermThree);
    lcd.setCursor(8,2);
    lcd.print(" ");
  }
  if (thermCount>3) {
    lcd.setCursor(14,2);
    printTemperature(thermFour);
    lcd.setCursor(19,2);
    lcd.print(" ");
  }
}
/*void printTime() {
if ((59-minute())<10) {lcd.print("0");}
  lcd.print(59-minute());
  lcd.print(":");
  if ((59-second())<10) {lcd.print("0");}
  lcd.print(59-second());
}
*/
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
// Connections:
// LCD Pin = L
// Arduino Pin = A
// L(4,5,6)->Ad(12,11,10) L(15)->(41ohm)->Ad(9) L(11,12,13,14)->Ad(5,4,3,2) 
// L(16)-> gnd
// L(15)-> (1kohm) -> gnd
// L(2)-> +5v    L(1)-> gnd
// thermistor yellow (bus) -> A(7)
// thermister black -> gnd
// thermister red -> +5v
// thermister red -> 4.7kohm -> thermister yellow

