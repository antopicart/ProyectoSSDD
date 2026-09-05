#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Clase base ABSTRACTA para todos los sensores (y el reloj) del ESP8266.
// Define QUÉ debe poder hacer cualquier sensor, no CÓMO -- eso lo
// completa cada clase hija (BMP280 por I2C, DHT22 digital, LDR por ADC,
// DS3231 también por I2C pero devolviendo tiempo en vez de una medición).
class Sensor {
  protected:
    uint8_t pin;          // pin al que está conectado (0 si usa I2C)
    float ultimaLectura;  // último valor leído
    bool inicializado;    // si inicializar() se ejecutó con éxito

  public:
    Sensor(uint8_t pinAsignado);

    virtual bool inicializar() = 0;
    virtual float leer() = 0;

    float obtenerUltimaLectura();
    bool estaInicializado();

    virtual ~Sensor();
};

#endif