// ============================================
//  TEST EMISOR - nRF24L01 - ESP8266
// ============================================
#include <Arduino.h>
#include <RF24.h>
#include <SPI.h>


#define PIN_CE   D1
#define PIN_CSN  D2

const byte RADIO_ADDRESS[6] = "00001";
#define RADIO_CHANNEL 90

RF24 radio(PIN_CE, PIN_CSN);

uint32_t counter = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println();
  Serial.println(F("=== TEST EMISOR ESP8266 ==="));

  if (!radio.begin()) {
    Serial.println(F("[ERROR] nRF24 NO detectado. Revisa cableado y alimentacion."));
    while (1) { delay(1000); }
  }
  Serial.println(F("[OK] nRF24 detectado."));

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RADIO_CHANNEL);
  radio.setRetries(5, 15);
  radio.openWritingPipe(RADIO_ADDRESS);
  radio.stopListening();

  Serial.println(F("--- Configuracion aplicada ---"));
  radio.printPrettyDetails();
  Serial.println(F("------------------------------"));
  Serial.println(F("Iniciando envios..."));
}

void loop() {
  char msg[16];
  snprintf(msg, sizeof(msg), "PING-%lu", (unsigned long)counter);

  bool ok = radio.write(&msg, sizeof(msg));

  Serial.print(F("Enviando: "));
  Serial.print(msg);
  Serial.print(F(" -> "));
  Serial.println(ok ? F("ACK OK") : F("SIN ACK"));

  counter++;
  delay(1000);
}