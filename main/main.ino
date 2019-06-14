#include "config.h"
#include "valve.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <coap-simple.h>
#include <Preferences.h>
#include "sensors.h"

// ---- TO DO ------
// 1. Add watchdog
// 2. Add sensor client
// 3. Add storage of sensor
// 4. Add time/scheduling

volatile uint32_t flowPulse = 0;

Preferences preferences;
Sensors sensors;

String wifiSSID, wifiPassword;
IPAddress serverAddress;

WiFiUDP udp;
Coap coap(udp);
Valve valve(VALVE_PIN);

void setup()
{
  Serial.begin(115200);
  preferences.begin("wifi", false);
  wifiSSID = preferences.getString("ssid", WIFI_SSID);
  wifiPassword = preferences.getString("password", WIFI_PASSWORD);
  preferences.end();
  preferences.begin("server", false);
  serverAddress.fromString(preferences.getString("ipaddr", SERVER_IP));
  preferences.end();
  preferences.begin("sensors", false);
  sensors.setup(preferences.getULong("interval", 10000));

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  if (MDNS.begin("garden"))
  {
    Serial.println("MDNS responder started");
  }

  //coap routes
  setupCOAPRoutes();

  // start coap server/client
  coap.start();

  // setup light sensor
  //setupLight();
  preferences.end();
  attachInterrupt(4, magnet_detect, RISING);
}

void loop()
{
  valve.loop();
  coap.loop();
  sensors.loop();
}

void magnet_detect()
{
  flowPulse++;
}
