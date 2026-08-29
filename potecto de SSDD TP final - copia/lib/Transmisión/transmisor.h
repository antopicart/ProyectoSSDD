#ifndef TRANSMISOR_H
#define TRANSMISOR_H

#include <Arduino.h>
#include <RF24.h>

// Encapsula el módulo NRF24L01: el resto del programa no necesita
// saber nada de SPI, "pipes" ni direcciones de radio, solo llama
// inicializar() y enviar(). Si el día de mañana cambian de módulo
// de radio, solo se reescribe esta clase, nada más del proyecto.
class Transmisor {
  private:
    RF24 radio;              // objeto de la librería RF24, maneja el módulo por SPI
    const uint64_t direccion = 0xF0F0F0F0E1LL; // "nombre" del canal de comunicación (debe ser igual en el receptor)

  public:
    // CE y CSN son los dos pines digitales que eligieron para el módulo
    // (los de SPI -SCK/MOSI/MISO- son fijos y la librería los usa solos).
    Transmisor(uint8_t pinCE, uint8_t pinCSN);

    bool inicializar();
    bool enviar(const char* datos, uint8_t longitud);
};

#endif