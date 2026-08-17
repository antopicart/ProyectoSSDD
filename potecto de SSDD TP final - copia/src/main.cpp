#include <Arduino.h>
#include "SensorBMP280.h"
#include "SensorDHT22.h"
#include "SensorLDR.h"

// definimos los pines que vamos a usar en el arduino
#define PIN_DHT22 2
#define PIN_LDR   A0

// Creamos los OBJETOS de cada clase (instanciamos una clase).
SensorBMP280 sensorPresion;
SensorDHT22  sensorHumedad(PIN_DHT22);
SensorLDR    sensorLuz(PIN_LDR);

void setup() {
  Serial.begin(9600);

  // Cada objeto se inicializa llamando a SU PROPIA versión de inicializar(),
  // aunque desde acá se llame igual para los tres (polimorfismo).
  if (!sensorPresion.inicializar()) {
    Serial.println("Error: no se pudo inicializar el BMP280");
  }
  if (!sensorHumedad.inicializar()) {
    Serial.println("Error: no se pudo inicializar el DHT22");
  }
  sensorLuz.inicializar();

  Serial.println("Sensores listos.");
}

void loop() {
  // Cada objeto sabe leer su propio sensor, sin que el loop()
  // necesite saber si es I2C, digital o analógico.
  float presion    = sensorPresion.leer();          // hPa
  float altitud    = sensorPresion.leerAltitud();    // metros relativos
  float humedad    = sensorHumedad.leer();           // %
  float temperatura = sensorHumedad.leerTemperatura(); // °C (fuente principal)
  float luz        = sensorLuz.leer();                // valor crudo 0-1023

  // Armamos el texto que después se va a transmitir por radio.
  String paquete = "T:" + String(temperatura, 1) +
                    ",H:" + String(humedad, 1) +
                    ",P:" + String(presion, 1) +
                    ",A:" + String(altitud, 1) +
                    ",L:" + String(luz, 0);

  Serial.println(paquete);

  delay(3000); // esperamos 3 segundos entre lecturas
}