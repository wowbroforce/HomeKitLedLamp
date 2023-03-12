
#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c

extern "C" homekit_server_config_t accessory_config;
extern "C" homekit_characteristic_t cha_on;
extern "C" homekit_characteristic_t cha_bright;
extern "C" homekit_characteristic_t cha_sat;
extern "C" homekit_characteristic_t cha_hue;

static uint32_t next_heap_millis = 0;

bool is_on = false;
float current_hue = 0;
float current_sat = 0;
uint8_t current_brightness = 0;
uint8_t correctedHue = current_hue / 360.0 * 255;
uint8_t correctedSat = current_sat / 100.0 * 255;
uint8_t correctedVal = current_brightness / 100.0 * 255;


void setupHomeKit() {
  Serial.println("HomeKit set up started...");
  cha_on.setter = set_on;
  cha_bright.setter = set_bright;
  cha_sat.setter = set_sat;
  cha_hue.setter = set_hue;
  
  arduino_homekit_setup(&accessory_config);

  Serial.println("HomeKit set up complete");
  delay(1000);

  Serial.println("Reading HomeKit saved values from EEPROM...");

  restoreHomeKitValues();
  updateColor();

  Serial.println("Done reading HomeKit saved values");
}

void updateHomeKit() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}

void restoreHomeKitValues() {
  // read and convert values
  is_on = EEPROM.read(ON_OFF_STATE);
  Serial.print(" - > ON_OFF_STATE = "); Serial.println(is_on);
  current_hue = EEPROM.read(HUE_STATE) / 255.0 * 360.0;
  Serial.print(" - > HUE_STATE = "); Serial.println(current_hue);
  current_sat = EEPROM.read(SAT_STATE) / 255.0 * 100.0;
  Serial.print(" - > SAT_STATE = "); Serial.println(current_sat);
  current_brightness = EEPROM.read(VAL_STATE) / 255.0 * 100.0;
  Serial.print(" - > VAL_STATE = "); Serial.println(current_brightness);
  
  // sync values
  cha_on.value.bool_value = is_on;
  cha_hue.value.float_value = current_hue;
  cha_sat.value.float_value = current_sat;
  cha_bright.value.int_value = current_brightness;
}

void set_on(const homekit_value_t v) {
  bool on = v.bool_value;
  cha_on.value.bool_value = on; //sync the value

  is_on = on;

  updateColor();
  
  EEPROM.write(ON_OFF_STATE, is_on);
}

void set_hue(const homekit_value_t v) {
  Serial.println("set_hue");
  float hue = v.float_value;
  cha_hue.value.float_value = hue; //sync the value

  current_hue = hue;
  correctedHue = current_hue / 360.0 * 255;

  updateColor();
  
  EEPROM.write(HUE_STATE, correctedHue);
}

void set_sat(const homekit_value_t v) {
  Serial.println("set_sat");
  float sat = v.float_value;
  cha_sat.value.float_value = sat; //sync the value

  current_sat = sat;
  correctedSat = current_sat / 100.0 * 255;

  updateColor();

  EEPROM.write(SAT_STATE, correctedSat);
}

void set_bright(const homekit_value_t v) {
  Serial.println("set_bright");
  int bright = v.int_value;
  cha_bright.value.int_value = bright; //sync the value

  current_brightness = bright;
  correctedVal = current_brightness / 100.0 * 255;

  updateColor();

  EEPROM.write(VAL_STATE, correctedVal);
}

void updateColor() {
  if (is_on) {
    homeKitColor = CHSV(correctedHue, correctedSat, correctedVal);
  } else {
    homeKitColor = CRGB::Black;
  }
  Serial.print("H = ");
  Serial.print(current_hue);
  Serial.print("; S = ");
  Serial.print(current_sat);
  Serial.print("; V = ");
  Serial.print(current_brightness);
  Serial.print("; corrected H = ");
  Serial.print(correctedHue);
  Serial.print("; corrected S = ");
  Serial.print(correctedSat);
  Serial.print("; corrected V = ");
  Serial.print(correctedVal);
  Serial.println();
  homeKitColorUpdated = true;
}
