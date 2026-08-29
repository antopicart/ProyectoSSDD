#ifndef BMP280_H
#define BMP280_H

#include "Sensor.h"
#include <Adafruit_BMP280.h>

// Hereda de Sensor ("es un" Sensor). Se comunica por I2C.
// Además de presión (que es lo que devuelve leer(), su lectura
// "principal"), puede calcular altitud y tiene su propia temperatura
// interna, por eso agrega métodos propios además de los heredados.
class SensorBMP280 : public Sensor {
  private:
    Adafruit_BMP280 bmp;      // objeto de la librería de Adafruit que maneja el I2C
    float presionReferencia;  // presión tomada como "altura 0" al inicializar
    float ultimaAltitud;

  public:
    SensorBMP280();

    bool inicializar() override;  // implementación específica: usa I2C
    float leer() override;        // devuelve presión en hPa

    float leerTemperatura();      // temperatura del BMP280 (dato secundario/control)
    float leerAltitud();          // altitud relativa calculada con la presión de referencia
};

#endif