/******************************/
/* Medir Temperatura  ds18b20 */
/******************************/

/***  Librería  ***/

#include <OneWire.h>
#include <DallasTemperature.h>

/**  Definiciones **/

#define Pin 2    // Se declara el pin donde se conectará la data


OneWire ourWire (Pin);  //Se establece el pin declarado como bus para la comunicación  OneWire

DallasTemperature sensors (&ourWire); //Se llama a la librería DallasTemeprature


//** Programar  **//

void setup() {
  delay (1000);
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); //prepara el sensor para la lecutra
  Serial.print (sensors.getTempCByIndex (0) * 1000); //se lee e imprime la temperatura en grados centigrados
  Serial.println (" Grados Centigrados");

  delay (125);
}
