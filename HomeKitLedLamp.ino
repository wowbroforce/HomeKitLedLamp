#include <FastLED.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <arduino_homekit_server.h>
#include "Buffer.h"
// #include "FireEffect.h"
#include "Renderer.h"

#define WIDTH 16                // matrix width
#define HEIGHT 16               // matrix height
#define NUM_LEDS WIDTH * HEIGHT // total number of leds

// WiFi Manager
#define AC_SSID "HomeKitLedLamp"
#define AC_PASS "11111111"

// EEPROM
#define ON_OFF_STATE 200
#define HUE_STATE 201
#define SAT_STATE 202
#define VAL_STATE 203

CRGB homeKitColor;
bool homeKitColorUpdated = false;
Renderer renderer;
Buffer buffer(WIDTH, HEIGHT);

void setup() {
  // put your setup code here, to run once:
//  ESP.wdtDisable();
//
  renderer.setup(&buffer);

  Serial.begin(115200);
  Serial.println();
  delay(1000);
  
  Serial.println("starting WiFi manager to auto connect...");
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);
  wifiManager.autoConnect(AC_SSID, AC_PASS);
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  setupHomeKit();
}

void loop() { 
  if (homeKitColorUpdated) {
    buffer.fill(homeKitColor);
    homeKitColorUpdated = false;
  }

  renderer.update();

  updateHomeKit();
}
