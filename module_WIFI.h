#ifdef toggle_WIFI_ADP
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
WiFiEspClient espClient;

#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

WiFiClient espClient;
#endif

void init_WIFI(const char* ssid_WIFI, const char* password_WIFI) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);

    if (serialoutput) {
      Serial.println("Scan start ... ");
    }
    int n = WiFi.scanNetworks();

    if (serialoutput) {
      Serial.print(n); Serial.println(" network(s) found:");
    }

    for (int i = 0; i < n; i++)
    {
      if (WiFi.SSID(i) == ssid_WIFI) {
        ssid_WIFI_FOUND = true;
      }

      if (serialoutput) {
        Serial.println(WiFi.SSID(i));
      }
    }
    if (serialoutput) {
      Serial.println();
    }

    if (ssid_WIFI_FOUND) {
      if (serialoutput) {
        Serial.print("Connecting to ");
        Serial.println(ssid_WIFI);
      }

      WiFi.begin(ssid_WIFI, password_WIFI);
      WIFI_connect_timer = millis();

      while ((millis() - WIFI_connect_timer) < WIFI_connect_time)
      {
        delay(500);
        if (serialoutput) {
          Serial.print(".");
        }
      }

      randomSeed(micros());
      if ((WiFi.status() == WL_CONNECTED)) {
        if (serialoutput) {
          Serial.println("");
          Serial.println("WiFi connected");
          Serial.println("IP address: ");
          Serial.println(WiFi.localIP());
        }
      }
      else {
        if (serialoutput) {
          Serial.println("");
          Serial.print("Could not connect to wifi within "); Serial.print(WIFI_connect_time / 1000); Serial.println(" seconds.");
          Serial.println("Check your password or router status.");
        }
      }
    }
    else {
      if (serialoutput) {
        Serial.print("Network with SSID "); Serial.print(ssid_WIFI); Serial.println(" was not found.");
      }
    }
  }
}

void setup_function_WIFI(const char* ssid, const char* password_WIFI) {
#ifdef toggle_WIFI_ADP
  WiFi.init(serial_ADP);
#endif
  init_WIFI(ssid, password_WIFI);
  WIFI_scan_timer = millis();
}

void loop_function_WIFI(const char* ssid, const char* password_WIFI) {
  if (WiFi.status() != WL_CONNECTED && (millis() - WIFI_scan_timer) > WIFI_scan_time) {
    if (serialoutput) {
      Serial.print("Not connected to wifi for more than "); Serial.print(WIFI_scan_time / 1000); Serial.println(" seconds.");
      Serial.print("Trying to reconnect to SSID "); Serial.println(ssid_WIFI);
    }
    init_WIFI(ssid_WIFI, password_WIFI);
    WIFI_scan_timer = millis();
  }
}
