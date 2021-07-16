#include <EEPROM.h>
#include "GravityTDS.h"

#define TdsSensorPin A1
GravityTDS gravityTds; 

float temperature = 25, tdsValue = 0;


void setup() {
  Serial.begin (115200);
  gravityTds.setPin (TdsSensorPin);
  gravityTds.setAref (5.0); // voltaje de referencia en ADC, default 5.0V en Arduino UNO
  gravityTds.setAdcRange (1024);  //1024 para 10bit ADC; 4096 para 12bit ADC
  gravityTds.begin (); //inicialización
}

void loop() {
  //temperature = readTemperature(); //Sensor de temperatura
  gravityTds.setTemperature (temperature); //setea la temperatura y ejecuta la compesación de temperatura
  gravityTds.update(); //muestreo y cálculo
  tdsValue = gravityTds.getTdsValue(); //entonces objetn el valor
  Serial.print (tdsValue, 0);
  Serial.println ("ppm");
  delay (1000);
}
