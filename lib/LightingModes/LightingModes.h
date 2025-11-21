#ifndef LIGHTINGMODES_H
#define LIGHTINGMODES_H

#include <FastLED.h>

class LightingModes {
public:
  enum Mode { NORMAL = 0, CAUTION, RED_ALERT, DAMAGED, WARP };

  // Apply a simple mode. `on` is used for modes that toggle (e.g. RED_ALERT blink).
  static void applyMode(Mode mode, CRGB *leds, int numLeds, bool on = true);
  // Initialize lighting subsystem (sets brightness, clears LEDs and shows).
  static void begin(CRGB *leds, int numLeds, uint8_t brightness = 64);
};

#endif // LIGHTINGMODES_H
