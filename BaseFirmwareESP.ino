// TOGGLE DEFINITIONS
#define toggle_WIFI         // enables wifi functionality
//#define toggle_WIFI_ADP   // switch for using serial wifi adapter
#define toggle_OTA          // enables OTA (Over The Air) update functionality
#define toggle_MQTT         // enables MQTT communication
#define toggle_NTP        // enables NTP synochronization
#define toggle_LCD

#define serialoutput true   // toggles output on serial

// GENERAL INCLUDES
#include <ArduinoJson.h>
DynamicJsonBuffer jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
String sPayload;
char* cPayload;
#include "module_SENSORS.h"

#if (serialoutput)
int baudrate = 74880; // baudrate for serial communication; 74880 is used during boot
#endif

#ifdef toggle_WIFI
#define toggle_TELNET // when WIFI is enabled, TELNET server is automatically created
const char* ssid_WIFI = "DaVinciSmartDevices";
const char* password_WIFI = "Wbhdvc2017!";
int WIFI_scan_time = 10000; // time to scan for wifi network with ssid ssid_WIFI
int WIFI_connect_time = 10000; // time to try to connect to wifi network with ssid ssid_WIFI

bool ssid_WIFI_FOUND = false;
int WIFI_scan_timer;
int WIFI_connect_timer;
#include "module_WIFI.h"
#endif

#ifdef toggle_WIFI_ADP
#define serial_ADP &Serial2
#endif

const uint16_t aport = 8260;
#include "module_TELNET.h" // TELNET is always included, although only started when WIFI is enabled

#ifdef toggle_OTA
#include "module_OTA.h"
const char* hostname_OTA = "WemosD1R2 Plantenbak 1";
const char* password_OTA = "123";
#endif

#ifdef toggle_MQTT
const char* token_MQTT = "uqG98uePNRDpwr7TStQo";
const char* server_MQTT = "192.168.100.1";
#include "module_MQTT.h"
#endif

#ifdef toggle_LCD
#include "module_LCD.h"
#endif

#ifdef toggle_NTP
int time_reboot = (((7 * 24) + 0) * 60 + 0) * 60; //reboot time in seconds
int time_ntp = (((1 * 24) + 0) * 60 + 0) * 60; // ntp refresh time in seconds
const char* ntpServerName = "time.nist.gov";
const int timeZone = 0;     // Central European Time
#include "module_NTP.h"
#endif

int looptime = 500;
int looptimer;

void setup() {
  if (serialoutput) {
    Serial.begin(baudrate);
    Serial.println();
  }

#ifdef toggle_WIFI
  setup_function_WIFI(ssid_WIFI, password_WIFI);
#endif

#ifdef toggle_TELNET
  setup_function_TELNET();
#endif

#ifdef toggle_OTA
  setup_function_OTA(hostname_OTA, password_OTA);
#endif

#ifdef toggle_MQTT
  setup_function_MQTT(server_MQTT);
#endif

#ifdef toggle_LCD
  setup_function_LCD();
#endif

#ifdef toggle_NTP
  setup_function_NTP();
#endif

  setup_function_SENSORS();

}

void loop() {
  looptimer = millis();

#ifdef toggle_WIFI
  loop_function_WIFI(ssid_WIFI, password_WIFI);
#endif

#ifdef toggle_OTA
  loop_function_OTA();
#endif

#ifdef toggle_NTP
  loop_function_NTP();
#endif

  loop_function_SENSORS();

#ifdef toggle_MQTT
  loop_function_MQTT();
#endif

#ifdef toggle_LCD
  loop_function_LCD();
#endif

  while ((millis() - looptimer) < looptime) {
    delay(100);
  }
}
