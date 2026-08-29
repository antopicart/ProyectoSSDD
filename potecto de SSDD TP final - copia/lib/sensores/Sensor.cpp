#include "Sensor.h"

// Constructor: inicializa los atributos comunes a todo sensor.
// Se llama automáticamente desde el constructor de cada clase hija
// (por ejemplo, en SensorBMP280.cpp vas a ver "SensorBMP280::SensorBMP280() : Sensor(0) {...}")
Sensor::Sensor(uint8_t pinAsignado) {
  pin = pinAsignado;
  ultimaLectura = 0.0;
  inicializado = false;
}

float Sensor::obtenerUltimaLectura() {
  return ultimaLectura; // devuelve el último valor leído sin volver a medir
}

bool Sensor::estaInicializado() {
  return inicializado;
}

// Destructor: vacío porque esta clase no reserva memoria dinámica,
// pero tiene que existir y ser virtual para que la herencia funcione bien.
Sensor::~Sensor() {}