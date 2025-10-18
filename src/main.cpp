#include <Arduino.h>
#include <FastLED.h>

// Basic NeoPixel (WS2812/WS2812B) red blink example for ESP32 (nodemcu-32s)
// Change LED_PIN to the pin you wired the data line to.

#define LED_PIN    13
#define NUM_LEDS    8
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define BRIGHTNESS  64

CRGB leds[NUM_LEDS];

unsigned long lastMillis = 0;
const unsigned long interval = 500; // milliseconds
bool ledOn = false;

void setup() {
  // Initialise serial (optional)
  Serial.begin(9600);
  delay(10);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  unsigned long now = millis();
  if (now - lastMillis >= interval) {
    lastMillis = now;
    ledOn = !ledOn;
    if (ledOn) {
      fill_solid(leds, NUM_LEDS, CRGB::Red);
    } else {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
    FastLED.show();
  }
}