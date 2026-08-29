#ifndef LDR_H
#define LDR_H

#include "Sensor.h"

// Hereda de Sensor. Se comunica por un pin analógico (ADC).
// Es el más simple de los tres: no necesita ninguna librería externa.
class SensorLDR : public Sensor {
  public:
    SensorLDR(uint8_t pinAsignado);

    bool inicializar() override;
    float leer() override; // devuelve un valor crudo 0-1023 según la luz recibida
};

#endif