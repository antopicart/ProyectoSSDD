#include <Arduino.h>
#include <Wire.h>

#include "Sensor.h"
#include "SensorBMP280.h"
#include "SensorDHT22.h"
#include "SensorLDR.h"
#include "SensorDS3231.h"
#include "Paquete.h"
#include "TimerConfig.h"

// #include "Transmisor.h"   // <- DESCOMENTAR cuando agreguemos la clase del NRF24

// ============================================================
//  ESP8266 - Recolección de datos (CanSat)
//  Por ahora arma el paquete (struct) y lo imprime por Serial.
//  La transmisión por NRF24 queda comentada, lista para sumar.
// ============================================================

// ---------- Pines (según el diagrama de conexión del satélite) ----------
#define PIN_SDA   D2  // BMP280 y DS3231 comparten el mismo bus I2C
#define PIN_SCL   D1
#define PIN_DHT22 D0  // único pin digital libre, ya que D1/D2 son I2C y D3-D7 son del NRF24
#define PIN_LDR   A0  // único pin analógico del ESP8266

// Pines reservados para el NRF24 (para cuando lo agreguemos):
// #define PIN_CE  D3
// #define PIN_CSN D4
// SCK, MOSI, MISO son fijos en el ESP8266: D5, D7, D6 respectivamente
// (coincide con lo que se ve en tu diagrama: CSK->D5, MO->D6, MI->D7)

// ---------- Objetos (uno por cada variable que pediste) ----------
SensorBMP280 sensorPresion;          // presión (y de paso, altitud y su propia temperatura)
SensorDHT22  sensorHumedad(PIN_DHT22); // humedad (y temperatura, la que usamos como fuente principal)
SensorLDR    sensorLuz(PIN_LDR);     // luz
SensorDS3231 sensorReloj;            // hora / timestamp

// Array de punteros a Sensor: permite inicializar y leer los 4 objetos
// de forma polimórfica, sin importar que cada uno se comunique distinto.
Sensor* sensores[4] = { &sensorPresion, &sensorHumedad, &sensorLuz, &sensorReloj };
const uint8_t CANTIDAD_SENSORES = 4;

Paquete paquete; // arma el struct final con todos los valores juntos

// Transmisor transmisor(PIN_CE, PIN_CSN); // <- DESCOMENTAR cuando agreguemos el NRF24

void setup() {
  Serial.begin(9600);

  // En el ESP8266 hay que indicarle a Wire (I2C) qué pines usar --
  // a diferencia del Arduino Uno/Nano, acá no son fijos por hardware.
  Wire.begin(PIN_SDA, PIN_SCL);

  // Inicializamos los 4 objetos (3 sensores + el reloj) de forma
  // uniforme gracias al polimorfismo.
  for (uint8_t i = 0; i < CANTIDAD_SENSORES; i++) {
    if (!sensores[i]->inicializar()) {
      Serial.print(F("Error al inicializar sensor n° "));
      Serial.println(i);
    }
  }

  configurarTimer(); // arranca el conteo de 3 segundos por hardware

  // if (!transmisor.inicializar()) {                     // <- DESCOMENTAR cuando agreguemos el NRF24
  //   Serial.println(F("Error: no se pudo inicializar el modulo NRF24L01"));
  // }

  Serial.println(F("Sistema listo (ESP8266 - recoleccion de datos)."));
}

void loop() {
  // No bloqueante: el loop() sigue libre todo el tiempo, y solo actúa
  // cuando la interrupción del Timer1 levantó la bandera.
  if (banderaLectura) {
    banderaLectura = false;

    // Leemos los 4 objetos a través del array. Para BMP280/DHT22/LDR,
    // leer() guarda su valor "principal" en ultimaLectura. Para el
    // reloj, leer() actualiza su timestamp interno (lo usamos después
    // con obtenerTimestamp(), que no pierde precisión).
    for (uint8_t i = 0; i < CANTIDAD_SENSORES; i++) {
      sensores[i]->leer();
    }

    // Datos "extra" que no forman parte de la interfaz genérica de Sensor,
    // por eso se piden directamente a los objetos concretos.
    float presion     = sensorPresion.obtenerUltimaLectura();
    float altitud      = sensorPresion.leerAltitud();
    float humedad      = sensorHumedad.obtenerUltimaLectura();
    float temperatura  = sensorHumedad.leerTemperatura(); // fuente principal de temperatura
    float luz          = sensorLuz.leerLux(); // convertido a escala de 0-6000 lux (ver SensorLDR.cpp)
    uint32_t timestamp = sensorReloj.obtenerTimestamp();  // valor sin pérdida de precisión

    // Armamos el paquete (struct) con todos los valores juntos
    paquete.actualizar(temperatura, humedad, presion, altitud, luz, timestamp);

    // Por ahora, como no tenemos el NRF24 todavía, mostramos el
    // contenido del struct por Serial para verificar que todo ande bien.
    paquete.imprimir();

    // ----- Acá iría la transmisión real, cuando agreguemos el NRF24 -----
    // PaqueteRadio datosParaEnviar = paquete.obtenerDatos();
    // bool enviado = transmisor.enviar(&datosParaEnviar, sizeof(datosParaEnviar));
    // if (!enviado) {
    //   Serial.println(F("Aviso: el receptor no confirmo recepcion del paquete"));
    // }
  }
}