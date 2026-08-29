#ifndef DHT22_H
#define DHT22_H

#include "Sensor.h"
#include <DHT.h>

// Hereda de Sensor. Se comunica por un único pin digital.
// Mide dos cosas (humedad y temperatura), por eso además del
// leer() heredado (que devuelve humedad) agrega leerTemperatura().
class SensorDHT22 : public Sensor {
  private:
    DHT dht; // objeto de la librería DHT que maneja el protocolo del sensor

  public:
    SensorDHT22(uint8_t pinAsignado);

    bool inicializar() override;
    float leer() override;        // devuelve humedad en % (lectura "principal")

    float leerTemperatura();      // temperatura en °C (fuente principal de temp. del proyecto)
};

#endif