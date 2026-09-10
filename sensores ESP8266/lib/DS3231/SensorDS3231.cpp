#include "SensorDS3231.h"

// El DS3231 va por I2C, no usa "pin" tradicional -> 0 a la clase base.
SensorDS3231::SensorDS3231() : Sensor(0) {
  ultimoTimestamp = 0;
}

bool SensorDS3231::inicializar() {
  inicializado = rtc.begin();

  if (inicializado && rtc.lostPower()) {
    // Si el módulo se quedó sin su pila de respaldo y perdió la hora,
    // lo reseteamos con la fecha/hora en que se compiló este programa
    // (mejor que nada, aunque no sea la hora "real" exacta).
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  return inicializado;
}

float SensorDS3231::leer() {
  DateTime ahora = rtc.now();
  ultimoTimestamp = ahora.unixtime();

  // Guardamos también en "ultimaLectura" (float) solo por consistencia
  // con la clase base -- para el paquete real se usa obtenerTimestamp().
  ultimaLectura = (float) ultimoTimestamp;
  return ultimaLectura;
}

uint32_t SensorDS3231::obtenerTimestamp() {
  return ultimoTimestamp;
}