#include "LDR.h"

SensorLDR::SensorLDR(uint8_t pinAsignado) : Sensor(pinAsignado) {}

bool SensorLDR::inicializar() {
  pinMode(pin, INPUT); // configura el pin como entrada analógica
  inicializado = true;
  return inicializado;
}

float SensorLDR::leer() {
  // analogRead devuelve un valor entre 0 y 1023 (resolución de 10 bits
  // del ADC del ATmega328). Se puede convertir a porcentaje o lux
  // después, con una calibración, si hace falta más adelante.
  ultimaLectura = analogRead(pin);
  return ultimaLectura;
}