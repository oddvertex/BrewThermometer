//
// Wine Cellar Monitor
//

#include <OneWire.h>
#include <DallasTemperature.h>

#include <dht.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// LCD definitions
#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// Thermistor definitions
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Temp Humidity sensor definitions
dht DHT;
#define DHTpin 11

void setup() {
  // LCD
  lcd.begin(20,4);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home (); // go home
 
  // Thermistor
  sensors.begin();
  
  // TH sensor
}

void loop() {
  // Just redraw everything every time
  DHT.read11(DHTpin);
  sensors.requestTemperatures();
  
  lcd.clear();
  lcd.print("Steve's Wine Cellar"); 
   
  // Room Temp and Humidity
  lcd.setCursor(0, 1);
  lcd.print("Temp: "); lcd.print(DHT.temperature*9./5+32, 1); lcd.print("F");
  lcd.setCursor(0, 2);
  lcd.print("Humidity: "); lcd.print(DHT.humidity, 1); lcd.print("%");
  
  // Bottle Temperature

  lcd.setCursor(0, 3);
  lcd.print("Bottle temp: "); lcd.print(sensors.getTempFByIndex(0), 1); lcd.print("F");
  
  // and wait a little
  delay(1000);
}

