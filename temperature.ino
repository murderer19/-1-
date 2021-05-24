

#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#define RELAY1  4  // Relay heating
#define RELAY2  6  // Relay cooling

int red = 8; // red LED heating
int blue = 2; // blue LED cooling

#define BACKLIGHT_PIN 13
#define ONE_WIRE_BUS 7
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(20,4);
  lcd.backlight();

pinMode(red, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(RELAY1, OUTPUT);
pinMode(RELAY2, OUTPUT);

    }

void loop() {
lcd.setCursor(0, 0);
  lcd.print("    TEMP CONTROL");
  
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  lcd.setCursor(0, 2);
  lcd.print("      ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print("\337C");
  
    if(temperature < 25)
    {
digitalWrite(red,HIGH);
digitalWrite(blue,LOW);
 
      lcd.setCursor(0, 3);
      lcd.print("      Heating");
 
digitalWrite(RELAY1,0); 
digitalWrite(RELAY2,1);   
           }
    else if(temperature > 25)
    {
digitalWrite(RELAY1,1);
digitalWrite(RELAY2,0); 
digitalWrite(red,LOW);
digitalWrite(blue,HIGH);

 lcd.setCursor(0, 4);
      lcd.print("      Cooling ");
      lcd.setCursor(0, 3);
      
}                 
} 
