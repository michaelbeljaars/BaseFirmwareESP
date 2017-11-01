#include <ArduinoOTA.h>

void setup_function_OTA(const char* hostname_OTA, const char* password_OTA) {
  // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  if (hostname_OTA) {
    ArduinoOTA.setHostname(hostname_OTA);
  }

  // No authentication by default
  if (password_OTA) {
    ArduinoOTA.setPassword(password_OTA);
  }

  ArduinoOTA.onStart([]() {
    if (serialoutput) {
      printlnDebug("Start");
    }
  });

  ArduinoOTA.onEnd([]() {
    if (serialoutput) {
      printlnDebug("\nEnd");
    }
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    if (serialoutput) {
      //printfDebug("Progress: %u%%\r", (progress / (total / 100)));
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    if (serialoutput) {
      //printfDebug("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) printlnDebug("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) printlnDebug("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) printlnDebug("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) printlnDebug("Receive Failed");
      else if (error == OTA_END_ERROR) printlnDebug("End Failed");
    }
  });

  ArduinoOTA.begin();
}

void loop_function_OTA() {
  ArduinoOTA.handle();
}

