#include "transmisor.h"

// El objeto "radio" de la librería RF24 necesita los pines CE y CSN
// desde el momento en que se crea, por eso se pasan acá en la lista
// de inicialización (no se puede hacer después, en otro método).
Transmisor::Transmisor(uint8_t pinCE, uint8_t pinCSN) : radio(pinCE, pinCSN) {}

bool Transmisor::inicializar() {
  if (!radio.begin()) {
    return false; // no se detectó el módulo (revisar cableado/capacitor)
  }

  radio.openWritingPipe(direccion);   // configura por dónde va a "escribir" los datos
  radio.setPALevel(RF24_PA_LOW);      // potencia de transmisión (LOW alcanza de sobra a poca distancia)
  radio.stopListening();              // este módulo solo transmite, nunca escucha

  return true;
}

bool Transmisor::enviar(const char* datos, uint8_t longitud) {
  // write() devuelve true si el receptor confirmó que le llegó el paquete
  // (el NRF24 sí tiene confirmación automática, a diferencia del LoRa básico)
  return radio.write(datos, longitud);
}

void Transmisor::desactivarConfirmacion() {
  radio.setAutoAck(false);
}
 
void Transmisor::desactivarConfirmacion() {
  radio.setAutoAck(false);   // no espera confirmación del receptor
  radio.setRetries(0, 0);    // no reintenta si algo falla
}
 