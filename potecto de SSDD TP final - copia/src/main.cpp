#include <Arduino.h>
#include "Sensor.h"
#include "BMP280.h"
#include "DHT22.h"
#include "LDR.h"
#include "PaqueteDatos.h"
#include "transmisor.h"

// ---------- Pines (ajustar según el cableado real) ----------
#define PIN_DHT22 2
#define PIN_LDR   A0
#define PIN_CE    7
#define PIN_CSN   8

// ---------- Objetos (instancias de cada clase) ----------
SensorBMP280 sensorPresion;
SensorDHT22  sensorHumedad(PIN_DHT22);
SensorLDR    sensorLuz(PIN_LDR);
PaqueteDatos paquete;
Transmisor   transmisor(PIN_CE, PIN_CSN);

// Array de PUNTEROS a Sensor: gracias al polimorfismo, podemos recorrer
// los tres sensores con un solo for, sin que importe que cada uno
// se comunique distinto (I2C, digital, ADC) por dentro.
Sensor* sensores[3] = { &sensorPresion, &sensorHumedad, &sensorLuz };
const uint8_t CANTIDAD_SENSORES = 3;

// Array donde se guardan las lecturas de cada ciclo, en el mismo
// orden que el array "sensores" de arriba (0=presión, 1=humedad, 2=luz)
float lecturas[3];

// ---------- Variable para la interrupción ----------
// "volatile" es OBLIGATORIO en variables que se modifican dentro de
// una interrupción: le dice al compilador que no la optimice ni
// asuma que su valor no cambia entre lecturas del loop().
volatile bool banderaLectura = false;

// ---------- Configuración del Timer1 para interrumpir cada 3 segundos ----------
// El ATmega328 (Uno/Nano) corre a 16 MHz. Usamos el Timer1 (de 16 bits)
// en modo CTC (Clear Timer on Compare Match): cuenta hasta un valor
// que nosotros definimos (OCR1A) y ahí dispara la interrupción sola,
// sin que el programa tenga que estar "mirando el reloj" (eso sería
// código bloqueante, justo lo que queremos evitar).
void configurarTimer() {
  noInterrupts(); // pausa todas las interrupciones mientras configuramos (evita estados inconsistentes)

  TCCR1A = 0; // limpiamos los registros de control del Timer1
  TCCR1B = 0;
  TCNT1  = 0; // el contador arranca en 0

  // Cálculo: con prescaler 1024, el timer cuenta 16.000.000 / 1024 = 15625 veces por segundo.
  // Para 3 segundos: 15625 * 3 = 46875 cuentas. Como cuenta desde 0, restamos 1.
  OCR1A = 46874;

  TCCR1B |= (1 << WGM12);               // modo CTC: reinicia el contador solo al llegar a OCR1A
  TCCR1B |= (1 << CS12) | (1 << CS10);  // prescaler = 1024
  TIMSK1 |= (1 << OCIE1A);              // habilita la interrupción por comparación en OCR1A

  interrupts(); // reactivamos las interrupciones
}

// ---------- Rutina de interrupción (ISR) ----------
// Se ejecuta SOLA cada 3 segundos, sin que el loop() la llame.
// Regla de oro de las ISR: tienen que ser lo más cortas posible.
// Por eso acá NO leemos los sensores (I2C/DHT tardan un rato y no
// es seguro hacer esas operaciones dentro de una interrupción),
// solo levantamos una "bandera" para avisarle al loop() que ya
// pasaron los 3 segundos.
ISR(TIMER1_COMPA_vect) {
  banderaLectura = true;
}

void setup() {
  Serial.begin(9600);

  // Inicializamos cada sensor llamando a SU PROPIA versión de
  // inicializar() a través del array (polimorfismo en acción).
  for (uint8_t i = 0; i < CANTIDAD_SENSORES; i++) {
    if (!sensores[i]->inicializar()) {
      Serial.print("Error al inicializar sensor n° ");
      Serial.println(i);
    }
  }

  if (!transmisor.inicializar()) {
    Serial.println("Error: no se pudo inicializar el modulo NRF24L01");
  }

  configurarTimer(); // arranca el conteo de 3 segundos por hardware

  Serial.println("Sistema listo.");
}

void loop() {
  // En vez de "delay(3000)" (que bloquea todo el programa y no deja
  // hacer nada más durante 3 segundos), preguntamos si la interrupción
  // ya levantó la bandera. El resto del tiempo, el loop() queda libre
  // para hacer otras cosas si hiciera falta (no bloqueante).
  if (banderaLectura) {
    banderaLectura = false; // bajamos la bandera hasta la próxima interrupción

    // Leemos los 3 sensores "genéricos" a través del array
    for (uint8_t i = 0; i < CANTIDAD_SENSORES; i++) {
      lecturas[i] = sensores[i]->leer();
    }

    // Datos extra que no forman parte de la interfaz común de Sensor
    // (por eso se piden directamente a los objetos concretos, no al array)
    float temperatura = sensorHumedad.leerTemperatura(); // fuente principal de temp.
    float altitud = sensorPresion.leerAltitud();

    // Armamos el paquete con todos los valores juntos
    paquete.actualizar(temperatura, lecturas[1], lecturas[0], altitud, lecturas[2]);
    // lecturas[1]=humedad, lecturas[0]=presión, lecturas[2]=luz (según el orden del array "sensores")

    const char* texto = paquete.obtenerTexto();
    Serial.println(texto); // para ver en el Monitor Serie mientras prueban

    bool enviado = transmisor.enviar(texto, paquete.obtenerLongitud());
    if (!enviado) {
      Serial.println("Aviso: el receptor no confirmó recepción del paquete");
    }
  }

  // Acá abajo podría ir cualquier otra tarea que no dependa del timer,
  // ya que el loop() nunca queda bloqueado esperando los 3 segundos.
}