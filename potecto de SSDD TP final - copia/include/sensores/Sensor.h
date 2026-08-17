#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Clase base ABSTRACTA: define QUÉ debe poder hacer todo sensor,
// pero no CÓMO lo hace cada uno (eso lo define cada clase hija).
// No se puede crear un objeto directamente de "Sensor", solo de sus hijas.
class Sensor {
  protected:
    uint8_t pin;          // pin al que está conectado el sensor
    float ultimaLectura;  // guarda el último valor leído
    bool inicializado;    // para saber si ya se llamó a inicializar()

  public:
    Sensor(uint8_t pinAsignado) {
      pin = pinAsignado;
      ultimaLectura = 0.0;
      inicializado = false;
    }

    // Métodos virtuales puros: cada clase hija ESTÁ OBLIGADA
    // a implementar su propia versión de inicializar() y leer().
    virtual bool inicializar() = 0;
    virtual float leer() = 0;

    // Método común a todos: devuelve el último valor sin volver a medir
    float obtenerUltimaLectura() {
      return ultimaLectura;
    }

    bool estaInicializado() {
      return inicializado;
    }

    virtual ~Sensor() {} // destructor virtual, buena práctica con herencia
};

#endif