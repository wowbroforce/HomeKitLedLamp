#include <FastLED.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <arduino_homekit_server.h>

// WiFi Manager
#define AC_SSID "HomeKitLedLamp"
#define AC_PASS "11111111"

// LED
#define BRIGHTNESS 40           // default brightness (0-255)
#define CURRENT_LIMIT 2000      // limit how much current in milliamps the LED matrix will pull from the power supply. Bigger value -> brigher light and more heat from leds and PSU. 0 - no limit, but you should check if your PSU can handle it.
#define LED_PIN D4              // LED pin
#define COLOR_ORDER GRB         // the order of color components on the leds.
#define WIDTH 16                // matrix width
#define HEIGHT 16               // matrix height
#define NUM_LEDS WIDTH * HEIGHT // total number of leds
// EEPROM
#define ON_OFF_STATE 200
#define HUE_STATE 201
#define SAT_STATE 202
#define VAL_STATE 203

CRGB leds[NUM_LEDS];
CRGB homeKitColor;
bool homeKitColorUpdated = false;

void setup() {
  // put your setup code here, to run once:
//  ESP.wdtDisable();
//
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)/*.setCorrection( TypicalLEDStrip )*/;
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);

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
    FastLED.showColor(homeKitColor);
    homeKitColorUpdated = false;
  }

  updateHomeKit();
}
