#include <EEPROM.h>
#include "GravityTDS.h"
//#include <LiquidCrustal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

//definimos los pines que utilizaremos
#define ONE_WIRE_BUS 7
#define TdsSensorPin A1

OneWire oneWire (ONE_WIRE_BUS);
GravityTDS gravityTds;

DallasTemperature sensors (&oneWire);

float tdsValue = 0;

void setup() {
  Serial.begin (115200);
  //lcd.begin (16,2);
  sensors.begin ();
  gravityTds.setPin (TdsSensorPin);
  gravityTds.setAref (5.0);
  gravityTds.setAdcRange (1024);
  gravityTds.begin();
}


void loop() {
  sensors.requestTemperatures();

  gravityTds.setTemperature (sensors.getTempCByIndex(0));
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();

  Serial.print (tdsValue, 0);
//  Serial.println (" ppm");
  //Serial.print ("La temperatura es: ");
  Serial.print (" ");
  Serial.println (sensors.getTempCByIndex(0) * 1000);

/*
  lcd.setCursor (0,1);
  lcd.print ("Temp: ");
  lcd.print (sensors.getTempCByIndex (0));
  lcd.print (" C");
*/

  delay (1000);
  //lcd.clear ();
}
