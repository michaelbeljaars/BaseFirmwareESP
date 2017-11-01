#include <PubSubClient.h>
#include <ArduinoJson.h>

PubSubClient client(espClient);

void setup_function_MQTT(const char* server_MQTT){
  client.setServer(server_MQTT, 1883);
}

void loop_function_MQTT() {
  client.loop();
}
