#ifndef PAQUETE_DATOS_H
#define PAQUETE_DATOS_H

#include <Arduino.h>

// Esta clase NO hereda de Sensor: no es un sensor, es un objeto
// que agrupa los valores de todos los sensores en un solo lugar
// y sabe convertirlos a texto listo para transmitir por radio.
//
// Usamos un buffer de char de tamaño FIJO en vez de la clase String
// de Arduino a propósito: concatenar Strings repetidamente puede
// fragmentar la poca memoria RAM del Arduino (2KB) con el tiempo.
// Un buffer fijo evita ese problema por completo.
class PaqueteDatos {
  private:
    float temperatura;
    float humedad;
    float presion;
    float altitud;
    float luz;

    char buffer[64]; // texto final armado, tamaño fijo (nunca crece ni se fragmenta)

  public:
    PaqueteDatos();

    // Carga los 5 valores actuales en el objeto
    void actualizar(float temp, float hum, float pres, float alt, float lux);

    // Arma el texto (ej: "T:23.5,H:60.0,P:1013.2,A:12.4,L:340") y lo devuelve.
    // Devuelve un puntero al buffer interno, no crea memoria nueva.
    const char* obtenerTexto();

    // Longitud real del texto armado, la necesita el Transmisor
    // para saber cuántos bytes mandar por radio.
    uint8_t obtenerLongitud();
};

#endif