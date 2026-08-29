#include "DHT22.h"

// Lista de inicialización: primero inicializa la parte heredada de
// Sensor (guarda el pin), y después construye el objeto "dht" de
// la librería, indicándole el pin y que es un modelo DHT22.
SensorDHT22::SensorDHT22(uint8_t pinAsignado) : Sensor(pinAsignado), dht(pinAsignado, DHT22) {}

bool SensorDHT22::inicializar() {
  dht.begin();
  delay(100); // espera puntual solo al arrancar, no se repite en el loop
  // El DHT22 no tiene fora de "confirmar" que está bien conectado
  // en el begin(), así que directamente asumimos que sí lo está.
  inicializado = true;
  return inicializado;
}

// leer() devuelve la HUMEDAD, que es la lectura "principal" que
// espera la clase base Sensor de este objeto.
float SensorDHT22::leer() {
  float humedad = dht.readHumidity();

  // El DHT22 puede fallar una lectura puntual y devolver NAN
  // (Not A Number). Si pasa, mantenemos el último valor válido
  // en vez de guardar un dato basura.
  if (!isnan(humedad)) {
    ultimaLectura = humedad;
  }

  return ultimaLectura;
}

// La temperatura la exponemos aparte (no es la lectura "principal"
// del Sensor base), porque es la que se usa como fuente PRINCIPAL
// de temperatura del proyecto completo (más confiable que la del BMP280).
float SensorDHT22::leerTemperatura() {
  float temp = dht.readTemperature();
  return temp; // puede devolver NAN si falla; se chequea al usarlo en el main
}