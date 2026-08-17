#ifndef SENSOR_DHT22_H
#define SENSOR_DHT22_H

#include "Sensor.h"
#include <DHT.h>

// Hereda de Sensor: "es un" Sensor, se comunica por 1 pin digital.
// Mide dos cosas (temperatura y humedad), por eso además de leer()
// (que devuelve la humedad por defecto) agrega leerTemperatura().
class SensorDHT22 : public Sensor {
  private:
    DHT dht;

  public:
    SensorDHT22(uint8_t pinAsignado) : Sensor(pinAsignado), dht(pinAsignado, DHT22) {}

    bool inicializar() override {
      dht.begin();
      delay(100);
      inicializado = true; // el DHT no tiene forma de confirmar conexión, se asume ok
      return inicializado;
    }

    // leer() devuelve la HUMEDAD, que es lo que la clase base espera
    // como "la" lectura principal de este sensor.
    float leer() override {
      float humedad = dht.readHumidity();
      if (!isnan(humedad)) {
        ultimaLectura = humedad;
      }
      return ultimaLectura;
    }

    // La temperatura del DHT22 la exponemos aparte, porque es
    // la que vamos a usar como fuente PRINCIPAL de temperatura
    // del proyecto (más confiable que la del BMP280, según charlamos).
    float leerTemperatura() {
      float temp = dht.readTemperature();
      return temp; // puede devolver NAN si falla la lectura, hay que chequearlo al usarlo
    }
};

#endif