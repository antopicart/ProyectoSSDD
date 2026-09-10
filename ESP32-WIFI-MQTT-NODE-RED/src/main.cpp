#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// ================================
// WIFI
// ================================
const char* ssid = "Alumnos2.4GHz";
const char* password = "alumnosfcyt";

// ================================
// MQTT
// ================================
const char* mqtt_server = "172.21.2.77";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Para evitar publicar "hola" muchas veces
bool mensajeEnviado = false;

void conectarWiFi() {
  Serial.print("Conectando al WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");

  Serial.print("IP del ESP32-S: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!client.connected()) {

    Serial.print("Conectando a Mosquitto...");

    if (client.connect("ESP32_S")) {

      Serial.println(" conectado");

      // Mandamos "hola" una sola vez
      if (!mensajeEnviado) {

        client.publish("prueba", "hola");

        Serial.println("Mensaje MQTT enviado:");
        Serial.println("Topic: prueba");
        Serial.println("Mensaje: hola");

        mensajeEnviado = true;
      }

    } else {

      Serial.print(" fallo, rc=");
      Serial.print(client.state());
      Serial.println(" - reintentando en 2 segundos");

      delay(2000);
    }
  }
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  conectarWiFi();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {

  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();
}