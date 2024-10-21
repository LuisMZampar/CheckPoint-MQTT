#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 21  

#define DHTTYPE DHT22  

const char* ssid = "Wokwi-GUEST"; 
const char* password = "";

const char* mqtt_server = "test.mosquitto.org";  
const char* mqtt_topic = "esp32/sensor_dht";     

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  reconnect();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao broker MQTT");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  // Enviando os dados no formato JSON
  String payload = "{\"temperatura\":" + String(t) + ", \"umidade\":" + String(h) + "}";
  client.publish(mqtt_topic, payload.c_str());

  Serial.println(payload);
  delay(5000);  
}
