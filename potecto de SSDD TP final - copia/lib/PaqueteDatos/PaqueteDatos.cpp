#include "PaqueteDatos.h"

PaqueteDatos::PaqueteDatos() {
  temperatura = 0;
  humedad = 0;
  presion = 0;
  altitud = 0;
  luz = 0;
  buffer[0] = '\0'; // string vacío al arrancar
}

void PaqueteDatos::actualizar(float temp, float hum, float pres, float alt, float lux) {
  temperatura = temp;
  humedad = hum;
  presion = pres;
  altitud = alt;
  luz = lux;
}

const char* PaqueteDatos::obtenerTexto() {
  // snprintf arma el texto directamente DENTRO del buffer fijo,
  // sin crear objetos String temporales ni fragmentar memoria.
  // %.1f = número decimal con 1 dígito después de la coma.
  snprintf(buffer, sizeof(buffer), "T:%.1f,H:%.1f,P:%.1f,A:%.1f,L:%.0f",
           temperatura, humedad, presion, altitud, luz);
  return buffer;
}

uint8_t PaqueteDatos::obtenerLongitud() {
  return strlen(buffer);
}