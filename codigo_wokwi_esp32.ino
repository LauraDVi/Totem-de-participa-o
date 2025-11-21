// Altere as informações de conexão para a sua rede
// As configurações atuais do código são apenas para testes

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "iot/reskilling/totem01";

#define TRIG_PIN 5
#define ECHO_PIN 18
#define BUTTON_PIN 4
#define PIR_PIN 15

unsigned long lastMsg = 0;
int etapaCount = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWifi() {
  Serial.println();
  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32-Reskilling")) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando de novo...");
      delay(2000);
    }
  }
}

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);

  setupWifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();

  float distancia = readDistanceCM();
  bool alunoAproximou = (distancia < 80.0);

  bool botaoPressionado = (digitalRead(BUTTON_PIN) == LOW);
  if (botaoPressionado) {
    etapaCount++;
    delay(300);
  }

  bool pirDetectado = (digitalRead(PIR_PIN) == HIGH);

  if (now - lastMsg > 2000) {
    lastMsg = now;

    String json = "{";
    json += "\"distance_cm\": " + String(distancia, 1) + ",";
    json += "\"student_near\": " + String(alunoAproximou ? "true" : "false") + ",";
    json += "\"step_count\": " + String(etapaCount) + ",";
    json += "\"presence\": " + String(pirDetectado ? "true" : "false");
    json += "}";

    Serial.println("Publicando: " + json);
    client.publish(mqtt_topic, json.c_str());
  }
}
