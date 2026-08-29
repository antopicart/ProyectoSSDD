// ======================================================
// PRUEBA DE CONEXIÓN ESP8266 + nRF24L01
// ======================================================

// Incluye las funciones principales de Arduino.
#include <Arduino.h>

// Incluye la librería SPI.
// El nRF24L01 se comunica con el ESP8266 mediante SPI.
#include <SPI.h>

// Incluye la librería RF24.
// Esta librería permite controlar el módulo nRF24L01.
#include <RF24.h>


// ======================================================
// CONFIGURACIÓN DEL nRF24L01
// ======================================================

// Creamos un objeto llamado "radio".
// Este objeto representa nuestro módulo nRF24L01.
//
// CE  está conectado al pin D2 del ESP8266.
// CSN está conectado al pin D8 del ESP8266.
RF24 radio(D2, D8);


// ======================================================
// SETUP
// ======================================================

// setup() se ejecuta una sola vez al encender
// o reiniciar el ESP8266.
void setup()
{
    // Inicia la comunicación serie con la computadora.
    // El Monitor Serie debe estar también a 115200 baudios.
    Serial.begin(115200);

    // Esperamos un segundo para que el ESP8266 termine de iniciar.
    delay(1000);

    Serial.println();
    Serial.println("Probando modulo nRF24L01...");


    // radio.begin() intenta iniciar la comunicación
    // entre el ESP8266 y el módulo nRF24L01.
    if (radio.begin())
    {
        // Si devuelve TRUE, significa que el ESP8266
        // pudo comunicarse con el nRF24L01.
        Serial.println("nRF24L01 detectado correctamente");
    }
    else
    {
        // Si devuelve FALSE, el ESP8266 no pudo
        // comunicarse con el nRF24L01.
        //
        // En ese caso revisaremos alimentación,
        // cableado y conexiones SPI.
        Serial.println("ERROR: no se detecta el nRF24L01");
    }
}


// ======================================================
// LOOP
// ======================================================

void loop()
{
    // Por ahora queda vacío.
    // Esta prueba solamente comprueba
    // si el ESP8266 reconoce el módulo.
}