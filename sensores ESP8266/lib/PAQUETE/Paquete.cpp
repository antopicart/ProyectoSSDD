#include "Paquete.h"

Paquete::Paquete() {
  datos.temperatura = 0;
  datos.humedad = 0;
  datos.presion = 0;
  datos.altitud = 0;
  datos.luz = 0;
  datos.timestamp = 0;
}

void Paquete::actualizar(float temp, float hum, float pres, float alt, float lux, uint32_t timestamp) {
  datos.temperatura = temp;
  datos.humedad = hum;
  datos.presion = pres;
  datos.altitud = alt;
  datos.luz = lux;
  datos.timestamp = timestamp;
}

PaqueteRadio Paquete::obtenerDatos() {
  return datos; // devuelve una copia del struct completo
}

void Paquete::imprimir() {
  Serial.println(F("========== Paquete (struct) =========="));
  Serial.print(F("Temperatura: ")); Serial.print(datos.temperatura); Serial.println(F(" C"));
  Serial.print(F("Humedad:     ")); Serial.print(datos.humedad);     Serial.println(F(" %"));
  Serial.print(F("Presion:     ")); Serial.print(datos.presion);     Serial.println(F(" hPa"));
  Serial.print(F("Altitud:     ")); Serial.print(datos.altitud);     Serial.println(F(" m"));
  Serial.print(F("Luz (ADC):   ")); Serial.println(datos.luz);
  Serial.print(F("Timestamp:   ")); Serial.println(datos.timestamp); // segundos desde 1/1/1970 (UTC)
  Serial.print(F("Tamaño del struct: ")); Serial.print(sizeof(PaqueteRadio)); Serial.println(F(" bytes"));
  Serial.println(F("========================================"));
}