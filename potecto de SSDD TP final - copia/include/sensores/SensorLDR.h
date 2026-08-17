#ifndef SENSOR_LDR_H
#define SENSOR_LDR_H

#include "Sensor.h"

// Hereda de Sensor: "es un" Sensor, se comunica por un pin analógico (ADC).
// Es el más simple de los tres: no necesita ninguna librería externa.
class SensorLDR : public Sensor {
  public:
    SensorLDR(uint8_t pinAsignado) : Sensor(pinAsignado) {}

    bool inicializar() override {
      pinMode(pin, INPUT);
      inicializado = true;
      return inicializado;
    }

    // Devuelve un valor "crudo" de 0 a 1023 (en Arduino) según la luz recibida.
    // Se puede convertir después a porcentaje o lux si hacen una calibración.
    float leer() override {
      ultimaLectura = analogRead(pin);
      return ultimaLectura;
    }
};

#endif