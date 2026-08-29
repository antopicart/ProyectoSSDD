#include "BMP280.h"

// El BMP280 no usa un "pin" tradicional (va por I2C, que usa
// siempre los mismos 2 pines fijos del Arduino), por eso le
// pasamos 0 al constructor de la clase base: no se usa acá.
SensorBMP280::SensorBMP280() : Sensor(0) {
  presionReferencia = 1013.25; // valor estándar a nivel del mar, se recalibra en inicializar()
  ultimaAltitud = 0.0;
}

bool SensorBMP280::inicializar() {
  // 0x76 es la dirección I2C más común del BMP280; algunos módulos
  // usan 0x77, si no lo detecta es lo primero a probar cambiar.
  inicializado = bmp.begin(0x76);

  if (inicializado) {
    delay(100); // pequeña espera puntual solo durante el arranque (no afecta el loop)
    // Tomamos la presión actual como referencia de "altura 0" del vuelo
    presionReferencia = bmp.readPressure() / 100.0F; // Pa -> hPa
  }

  return inicializado;
}

float SensorBMP280::leer() {
  ultimaLectura = bmp.readPressure() / 100.0F; // Pa -> hPa
  return ultimaLectura;
}

float SensorBMP280::leerTemperatura() {
  return bmp.readTemperature(); // en grados Celsius
}

float SensorBMP280::leerAltitud() {
  ultimaAltitud = bmp.readAltitude(presionReferencia); // metros relativos al punto de partida
  return ultimaAltitud;
}