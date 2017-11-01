#include <PubSubClient.h>

PubSubClient client(espClient);

void send_data_MQTT() {
  sPayload = "";
  root.printTo(sPayload);
  cPayload = &sPayload[0u];
  client.publish( "v1/devices/me/telemetry", cPayload);
}

void setup_function_MQTT(const char* server_MQTT) {
  client.setServer(server_MQTT, 1883);
}

void loop_function_MQTT() {
  send_data_MQTT();
  client.loop();
}
