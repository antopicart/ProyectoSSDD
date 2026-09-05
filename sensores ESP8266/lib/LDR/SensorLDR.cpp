#include "SensorLDR.h"

SensorLDR::SensorLDR(uint8_t pinAsignado) : Sensor(pinAsignado) {}

bool SensorLDR::inicializar() {
  pinMode(pin, INPUT);
  inicializado = true;
  return inicializado;
}

float SensorLDR::leer() {
  ultimaLectura = analogRead(pin);
  return ultimaLectura;
}

float SensorLDR::leerLux() {
  // El ADC del ESP8266 tiene 10 bits de resolución (0-1023) -- distinto
  // a los 12 bits (0-4095) del ESP32, por eso este número cambia según
  // la placa que se use.
  const float ADC_MAXIMO = 1023.0F;
  const float LUX_MAXIMO = 6000.0F;

  float valorCrudo = analogRead(pin);
  ultimaLectura = valorCrudo;

  // map() de Arduino funciona con floats truncando a enteros, así que
  // hacemos la cuenta manualmente para no perder precisión decimal:
  // invertimos la escala (ADC alto = oscuridad = 0 lux) y la reescalamos
  // a 0-6000.
  float lux = (ADC_MAXIMO - valorCrudo) * (LUX_MAXIMO / ADC_MAXIMO);

  // Por las dudas, limitamos el resultado a 0-6000 -- el ADC real puede
  // dar valores levemente fuera de 0-4095 por ruido eléctrico, y no
  // queremos un lux negativo o mayor al máximo definido.
  if (lux < 0) lux = 0;
  if (lux > LUX_MAXIMO) lux = LUX_MAXIMO;

  return lux;
}