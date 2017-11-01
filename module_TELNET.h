void setup_function_TELNET() {
  WiFiServer TelnetServer(aport);
  //WiFiClient Telnet;

  TelnetServer.begin();
  TelnetServer.setNoDelay(true);
}

void printDebug(const char* c) {
  //Prints to telnet if connected
  Serial.print(c);

#ifdef toggle_WIFI
  if (espClient && espClient.connected()) {
    espClient.print(c);
  }
#endif
}

void printlnDebug(const char* c) {
  //Prints to telnet if connected
  Serial.println(c);

#ifdef toggle_WIFI
  if (espClient && espClient.connected()) {
    espClient.println(c);
  }
#endif
}

void printfDebug(const char* c, float f) {
  //Prints to telnet if connected
  Serial.printf(c, f);

#ifdef toggle_WIFI
  if (espClient && espClient.connected()) {
    espClient.printf(c, f);
  }
#endif
}
