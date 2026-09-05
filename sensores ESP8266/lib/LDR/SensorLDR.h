#ifndef SENSOR_LDR_H
#define SENSOR_LDR_H

#include "Sensor.h"

class SensorLDR : public Sensor {
  public:
    SensorLDR(uint8_t pinAsignado);

    bool inicializar() override;
    float leer() override; // valor crudo del ADC (0-4095 en el ESP32, ojo que es distinto a AVR/ESP8266)

    // Convierte el valor crudo a una escala aproximada de "lux".
    // En este cableado, a MÁS luz el ADC da un valor MÁS BAJO, por eso
    // la conversión es invertida: ADC máximo (oscuridad) -> 0 lux,
    // ADC mínimo (luz máxima) -> 6000 lux. Es una escala relativa/estimada,
    // no una medición certificada en lux reales (para eso se necesitaría
    // un sensor calibrado como el BH1750), pero sirve para mostrar la
    // tendencia de luminosidad de forma más intuitiva que el valor crudo.
    float leerLux();
};

#endif