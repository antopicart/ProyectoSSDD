#ifndef SENSOR_DS3231_H
#define SENSOR_DS3231_H

#include "Sensor.h"
#include <RTClib.h>

// Hereda de Sensor para mantener la misma interfaz que el resto
// (inicializar/leer), aunque conceptualmente no "mide" algo físico:
// da la fecha/hora actual. Se comunica por I2C, igual que el BMP280,
// y puede compartir el mismo bus sin problema (direcciones distintas).
class SensorDS3231 : public Sensor {
  private:
    RTC_DS3231 rtc;
    uint32_t ultimoTimestamp; // guardado aparte de "ultimaLectura" (ver leer())

  public:
    SensorDS3231();

    bool inicializar() override;

    // Devuelve el timestamp como float SOLO para cumplir con la
    // interfaz común de Sensor. OJO: un float de 32 bits solo puede
    // representar enteros EXACTOS hasta 2^24 (~16.7 millones), y un
    // timestamp unix actual ronda los 1700 millones -- por lo tanto
    // este valor pierde precisión y NO debe usarse para el paquete real.
    float leer() override;

    // Este es el valor que hay que usar en el paquete: un entero de
    // 32 bits sin pérdida de precisión.
    uint32_t obtenerTimestamp();
};

#endif