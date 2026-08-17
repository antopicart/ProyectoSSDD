#ifndef SENSOR_BMP280_H
#define SENSOR_BMP280_H

#include "Sensor.h"
#include <Adafruit_BMP280.h>

// Hereda de Sensor: "es un" Sensor, pero se comunica por I2C
// y además puede calcular la altitud (algo extra que no tienen
// los otros sensores, por eso agrega sus propios métodos).
class SensorBMP280 : public Sensor {
  private:
    Adafruit_BMP280 bmp;      // objeto de la librería de Adafruit
    float presionReferencia;  // presión al nivel de partida (para altitud)
    float ultimaAltitud;

  public:
    // El BMP280 va por I2C, no usa un "pin" tradicional,
    // así que le pasamos 0 a la clase base (no se usa en este caso).
    SensorBMP280() : Sensor(0) {
      presionReferencia = 1013.25; // valor estándar a nivel del mar, se recalibra en inicializar()
      ultimaAltitud = 0.0;
    }

    bool inicializar() override {
      inicializado = bmp.begin(0x76); // dirección I2C típica del BMP280 (puede ser 0x77 según el módulo)
      if (inicializado) {
        // Tomamos la presión actual como referencia de "altura 0"
        delay(100); // pequeña espera para que el sensor tenga una primera lectura estable
        presionReferencia = bmp.readPressure() / 100.0F; // Pa -> hPa
      }
      return inicializado;
    }

    float leer() override {
      ultimaLectura = bmp.readPressure() / 100.0F; // devuelve presión en hPa
      return ultimaLectura;
    }

    float leerTemperatura() {
      return bmp.readTemperature(); // temperatura interna del BMP280 (dato secundario/control)
    }

    float leerAltitud() {
      ultimaAltitud = bmp.readAltitude(presionReferencia);
      return ultimaAltitud;
    }
};

#endif
