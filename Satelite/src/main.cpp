#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // configura el pin del LED integrado (pin 13) como salida
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // prende el LED
  delay(1000);                     // espera 1 segundo

  digitalWrite(LED_BUILTIN, LOW);  // apaga el LED
  delay(1000);                     // espera 1 segundo
}