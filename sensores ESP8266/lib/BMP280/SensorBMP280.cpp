#include "SensorBMP280.h"

SensorBMP280::SensorBMP280() : Sensor(0) {
  presionReferencia = 1013.25;
  ultimaAltitud = 0.0;
}

bool SensorBMP280::inicializar() {
  inicializado = bmp.begin(0x76); // 0x77 si no lo detecta con esta dirección
  if (inicializado) {
    delay(100);
    presionReferencia = bmp.readPressure() / 100.0F;
  }
  return inicializado;
}

float SensorBMP280::leer() {
  float lectura = bmp.readPressure() / 100.0F;

  // La presión atmosférica a baja altura (como la de la facultad) se
  // mueve normalmente entre ~950 y ~1050 hPa. Si sale de ese rango,
  // lo más probable es que el chip haya sufrido un reset momentáneo
  // (por ejemplo, por una caída de tensión) y perdió sus coeficientes
  // de calibración de fábrica -- begin() los vuelve a leer del chip.
  if (lectura < 900.0F || lectura > 1050.0F) {
    Serial.println(F("Aviso: presion fuera de rango plausible, reinicializando BMP280..."));
    inicializar();
    lectura = bmp.readPressure() / 100.0F; // reintenta una vez ya recalibrado
  }

  ultimaLectura = lectura;
  return ultimaLectura;
}

float SensorBMP280::leerTemperatura() {
  return bmp.readTemperature();
}

float SensorBMP280::leerAltitud() {
  ultimaAltitud = bmp.readAltitude(presionReferencia);
  return ultimaAltitud;
}