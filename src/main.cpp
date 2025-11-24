#include <Arduino.h>
#include <FastLED.h>
#include <LightingModes.h>
#include <../lib/Managers/connection_manager.h>
#include <../lib/Managers/mqtt_manager.h>
#include <esp_task_wdt.h>


#define LED_PIN    13
#define NUM_LEDS    8
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define BRIGHTNESS  64

CRGB leds[NUM_LEDS];
// Expose a runtime-accessible LED count for other translation units.
int g_num_leds = NUM_LEDS;

// Lighting is driven by MQTT messages — no periodic blinking here.

void setup() {
  // Initialise serial (optional)
  Serial.begin(9600);
  delay(10);

  // Initialize connection manager (ONLINE mode)
  initializeConnection(ONLINE);

  // Initialize MQTT manager
  mqttManager_begin();

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // Initialize lighting settings (brightness, clear, initial show)
  LightingModes::begin(leds, NUM_LEDS, BRIGHTNESS);
}

void loop() {
  // Reset watchdog to prevent timeout
  esp_task_wdt_reset();
  
  // Run MQTT manager loop (handles reconnects and incoming messages)
  mqttManager_loop();
  
  // Give other tasks some CPU time
  delay(10);
}