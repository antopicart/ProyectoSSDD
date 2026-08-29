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
        // Apaga la confirmación automática (auto-ack) del módulo. Con esto
    // desactivado, enviar() devuelve true apenas logra TRANSMITIR el
    // paquete, sin esperar ninguna respuesta del receptor -- útil
    // mientras prueban sin tener el receptor armado todavía, para no
    // ver avisos de "no confirmó recepción" en cada ciclo. OJO: una vez
    // que tengan los dos módulos comunicándose de verdad, conviene
    // volver a activarlo (no llamando a este método), porque el ACK es
    // lo que les permite saber si un paquete realmente llegó o se perdió.
    void desactivarConfirmacion();
 
    // Método SOLO para diagnóstico: apaga la confirmación automática
    // (auto-ack) y los reintentos, para descartar que el cuelgue sea
    // por esperar una confirmación que nunca llega (por ejemplo, por
    // alimentación insuficiente durante la transmisión).
    void desactivarConfirmacion();
};

#endif