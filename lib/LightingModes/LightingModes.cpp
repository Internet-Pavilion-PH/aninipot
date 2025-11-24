#include "LightingModes.h"

void LightingModes::applyMode(Mode mode, CRGB *leds, int numLeds, bool on) {
  switch (mode) {
    case NORMAL:
      // Soft white at low brightness
      fill_solid(leds, numLeds, CRGB::White);
      break;
    case CAUTION:
      // Amber (use an orange-ish color)
      fill_solid(leds, numLeds, CRGB(200, 120, 0));
      break;
    case RED_ALERT:
      if (on) fill_solid(leds, numLeds, CRGB::Red);
      else  fill_solid(leds, numLeds, CRGB::Black);
      break;
    case DAMAGED:
      // Flicker orange with occasional red 'sparks' handled by caller for randomness
      fill_solid(leds, numLeds, CRGB(180, 90, 0));
      break;
    case WARP:
      // Simple blue wash
      fill_solid(leds, numLeds, CRGB::Blue);
      break;
    case RED_ALERT_BLINK:
      // Use blinkRedAlert() function for timed blink behavior
      if (on) fill_solid(leds, numLeds, CRGB::Red);
      else fill_solid(leds, numLeds, CRGB::Black);
      break;
  }
}

void LightingModes::blinkRedAlert(CRGB *leds, int numLeds, unsigned long durationMs) {
  unsigned long startMs = millis();
  unsigned long blinkInterval = 200; // 200ms on/off (5 Hz)
  bool state = true;
  
  while (millis() - startMs < durationMs) {
    if (state) {
      fill_solid(leds, numLeds, CRGB::Red);
    } else {
      fill_solid(leds, numLeds, CRGB::Black);
    }
    FastLED.show();
    state = !state;
    delay(blinkInterval);
  }
  
  // Turn off after blinking
  fill_solid(leds, numLeds, CRGB::Black);
  FastLED.show();
}

void LightingModes::begin(CRGB *leds, int numLeds, uint8_t brightness) {
  FastLED.setBrightness(brightness);
  fill_solid(leds, numLeds, CRGB::Black);
  FastLED.show();
}
