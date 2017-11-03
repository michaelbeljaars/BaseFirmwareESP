#include <PubSubClient.h>

PubSubClient client(espClient);

void send_data_MQTT() {
  sPayload = "";
  root.printTo(sPayload);
  cPayload = &sPayload[0u];
  client.publish( "v1/devices/me/telemetry", cPayload);
}

void reconnect() {
  // Loop until we're reconnected
  int i = 0;
  while (!client.connected() && i < 5) {
    Serial.print("Connecting to Thingsboard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("Arduino Uno Device", token_MQTT, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 2 seconds]" );

      // Wait 5 seconds before retrying
      i++;
      delay(2000);
    }
  }
}

void setup_function_MQTT(const char* server_MQTT) {
  client.setServer(server_MQTT, 1883);
  reconnect();
}

void loop_function_MQTT() {
  if ( !client.connected() ) {
    reconnect();
  }

  send_data_MQTT();
  client.loop();
}
