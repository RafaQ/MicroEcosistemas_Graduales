// TODOS LOS SENSORES

//librería para PH
#include <Wire.h>

//librería para TDS
#include <EEPROM.h>
#include "GravityTDS.h"


//librería para Temp
#include <OneWire.h>
#include <DallasTemperature.h>

//definimos los pines a utilizar

#define ONE_WIRE_BUS 7
#define TdsSensorPin A1


OneWire oneWire (ONE_WIRE_BUS);
GravityTDS gravityTds;
DallasTemperature sensors (&oneWire);

float tdsValue = 0;

//variables para PH
float calibration_value = 21.34 - 0.7;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;
float ph_act;

void setup() {
  gravityTds.setPin (TdsSensorPin);
  gravityTds.setAref (5.0);
  gravityTds.setAdcRange (1024);
  gravityTds.begin();
  Wire.begin();
  Serial.begin (115200);

}

void loop() {
  sensors.requestTemperatures();

  gravityTds.setTemperature (sensors.getTempCByIndex(0));
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();


  //PH
  for (int i=0; i<10;i++)
  {
    buffer_arr[i] = analogRead(A0);
    delay (30);
  }
  for (int i=0; i<9; i++)
  {
  for (int j=i+1; j<10; j++)
  {
    if (buffer_arr[i] > buffer_arr[j])
    {
      temp = buffer_arr[i];
      buffer_arr[i] = buffer_arr[j];
      buffer_arr[j] = temp;
    }
  }
 }
 avgval = 0;
 for (int i=2; i<8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  ph_act = -5.70 * volt + calibration_value;
  

  Serial.print ("pH Val: ");
  Serial.print (ph_act);
  Serial.print (" | ");
  Serial.print ("conductividad: ");
  Serial.print (tdsValue, 0);
  Serial.print (" ppm");
  Serial.print (" | ");
  Serial.print ("Temperatura: ");
  Serial.println (sensors.getTempCByIndex(0));
  delay(500);
}
