#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Clase base ABSTRACTA para todos los sensores del proyecto.
// Define QUÉ debe poder hacer todo sensor (inicializar y leer),
// pero no CÓMO lo hace cada uno: eso lo completa cada clase hija.
// No se puede crear un objeto "Sensor" a secas, solo de sus hijas.
class Sensor {
  protected:
    uint8_t pin;          // pin al que está conectado (0 si usa I2C, que no usa "pin" tradicional)
    float ultimaLectura;  // guarda el último valor leído, para no tener que releer si no hace falta
    bool inicializado;    // indica si inicializar() ya se ejecutó con éxito

  public:
    // Constructor: solo declarado acá, implementado en Sensor.cpp
    Sensor(uint8_t pinAsignado);

    // Funciones virtuales PURAS (el "= 0"): cada clase hija está
    // OBLIGADA a implementarlas a su manera (I2C, digital, ADC, etc).
    // Esto es lo que hace que la clase sea abstracta.
    virtual bool inicializar() = 0;
    virtual float leer() = 0;

    // Métodos comunes a todos los sensores, sí implementados acá
    // (bueno, declarados acá e implementados en el .cpp)
    float obtenerUltimaLectura();
    bool estaInicializado();

    // Destructor virtual: buena práctica obligatoria cuando se usa
    // herencia con punteros a la clase base (como el array del main).
    virtual ~Sensor();
};

#endif