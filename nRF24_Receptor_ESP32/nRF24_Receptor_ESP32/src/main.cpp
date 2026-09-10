// ============================================
//  TEST RECEPTOR - nRF24L01 - ESP32
// ============================================
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

#define PIN_CE   4
#define PIN_CSN  5

const byte RADIO_ADDRESS[6] = "00001";
#define RADIO_CHANNEL 90

RF24 radio(PIN_CE, PIN_CSN);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println();
  Serial.println(F("=== TEST RECEPTOR ESP32 ==="));

  if (!radio.begin()) {
    Serial.println(F("[ERROR] nRF24 NO detectado. Revisa cableado y alimentacion."));
    while (1) { delay(1000); }
  }
  Serial.println(F("[OK] nRF24 detectado."));

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RADIO_CHANNEL);
  radio.openReadingPipe(1, RADIO_ADDRESS);
  radio.startListening();

  Serial.println(F("--- Configuracion aplicada ---"));
  radio.printPrettyDetails();
  Serial.println(F("------------------------------"));
  Serial.println(F("Esperando paquetes..."));
}

void loop() {
  if (radio.available()) {
    char msg[16] = {0};
    radio.read(&msg, sizeof(msg));
    Serial.print(F("[RECIBIDO] "));
    Serial.println(msg);
  }
}