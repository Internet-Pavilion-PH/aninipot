#include "LightingModes.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>

#ifdef BOARD_ESP32_DEV
  #define LED_PIN   13

    // Max is 255, 32 is a conservative value to not overload
  // a USB power supply (500mA) for 12x12 pixels.
  #define BRIGHTNESS 100

  // Define matrix width and height.
  #define mw 5
  #define mh 6

  #define LED_BLACK    0
  #define LED_BLUE     255

  int counter = 0;
  int numImage = 0;

  // When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
  // Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
  // example for more information on possible values.
  Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, LED_PIN,
      NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
      NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
      NEO_GRB            + NEO_KHZ800);
      
  static const uint16_t PROGMEM
  // These bitmaps were written for a backend that only supported
  // 4 bits per color with Blue/Green/Red ordering while neomatrix
  // uses native 565 color mapping as RGB.
  // I'm leaving the arrays as is because it's easier to read
  // which color is what when separated on a 4bit boundary
  // The demo code will modify the arrays at runtime to be compatible
  // with the neomatrix color ordering and bit depth.

  RGB_bmp[][64] = {

  //green wifi pattern
  {
    0x5A0,	0xFFF,	0xFFF,	0xFFF,	0x5A0,
    0xFFF,	0x5A0,	0x5A0,	0x5A0,	0xFFF,
    0x5A0,	0x5A0,	0xFFF,	0x5A0,	0x5A0,
    0x5A0,	0xFFF,	0x5A0,	0xFFF,	0x5A0,
    0x5A0,	0x5A0,	0x5A0,	0x5A0,	0x5A0,
    0x5A0,	0x5A0,	0xFFF,	0x5A0,	0x5A0,


  },

  //Heart pattern
  {
  0x000,	0x00F,	0x000,	0x00F,	0x000,
  0x00F,	0x00F,	0x00F,	0x00F,	0x00F,
  0x00F,	0x00F,	0x00F,	0x00F,	0x00F,
  0x00F,	0x00F,	0x00F,	0x00F,	0x00F,
  0x000,	0x00F,	0x00F,	0x00F,	0x000,
  0x000,	0x000,	0x00F,	0x000,	0x000,


  },

    //thumbs up
  {
  0xFFF,	0xFFF,	0xB70,	0xB70,	0xFFF,
  0xFFF,	0xB70,	0xB70,	0xFFF,	0xFFF,
  0xB70,	0xEA0,	0xB70,	0xB70,	0xB70,
  0xB70,	0xB70,	0xB70,	0xEA0,	0xB70,
  0xB70,	0xEA0,	0xB70,	0xB70,	0xB70,
  0xB70,	0xB70,	0xB70,	0xFFF,	0xFFF,


  },

  //Heart in heart pattern
  {
  0x000,	0x00F,	0x000,	0x00F,	0x000,
  0x00F,	0xFFF,	0x00F,	0xFFF,	0x00F,
  0xFFF,	0xFFF,	0xFFF,	0xFFF,	0xFFF,
  0x00F,	0xFFF,	0xFFF,	0xFFF,	0x00F,
  0x000,	0x00F,	0xFFF,	0x00F,	0x000,
  0x000,	0x000,	0x00F,	0x000,	0x000,


  },

  //emoticon
  {
  0x000,	0x0BF,	0x0BF,	0x0BF,	0x000,
  0x0BF,	0x0BF,	0x0BF,	0x0BF,	0x0BF,
  0x0BF,	0x000,	0x0BF,	0x000,	0x0BF,
  0x0BF,	0x0BF,	0x0BF,	0x0BF,	0x0BF,
  0x0BF,	0x0BF,	0x000,	0x0BF,	0x0BF,
  0x000,	0x0BF,	0x0BF,	0x0BF,	0x000,


  },

  //Hi text pattern
  {
  0xFFF,	0x000,	0xFFF,	0x000,	0xFFF,
  0xFFF,	0x000,	0xFFF,	0x000,	0x000,
  0xFFF,	0x000,	0xFFF,	0xFFF,	0xFFF,
  0xFFF,	0x000,	0xFFF,	0x000,	0xFFF,
  0xFFF,	0x000,	0xFFF,	0x000,	0xFFF,
  0xFFF,	0x000,	0xFFF,	0x000,	0xFFF,


  },

  };


  // Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
  void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    uint16_t RGB_bmp_fixed[w * h];
    for (uint16_t pixel = 0; pixel < w * h; pixel++) {
      uint8_t r, g, b;
      uint16_t color = pgm_read_word(bitmap + pixel);

      //Serial.print(color, HEX);
      b = (color & 0xF00) >> 8;
      g = (color & 0x0F0) >> 4;
      r = color & 0x00F;
      //Serial.print(" ");
      //Serial.print(b);
      //Serial.print("/");
      //Serial.print(g);
      //Serial.print("/");
      //Serial.print(r);
      //Serial.print(" -> ");
      // expand from 4/4/4 bits per color to 5/6/5
      b = map(b, 0, 15, 0, 31);
      g = map(g, 0, 15, 0, 63);
      r = map(r, 0, 15, 0, 31);
      //Serial.print(r);
      //Serial.print("/");
      //Serial.print(g);
      //Serial.print("/");
      //Serial.print(b);
      RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
    // Serial.print(" -> ");
      //Serial.print(pixel);
      //Serial.print(" -> ");
      //Serial.println(RGB_bmp_fixed[pixel], HEX);
    }
    matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
  }

  void display_rgbBitmap(uint8_t bmp_num) {
  static uint16_t bmx, bmy;

  fixdrawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 5, 6);
  bmx += 6;
  if (bmx >= mw) bmx = 0;
  if (!bmx) bmy += 6;
  if (bmy >= mh) bmy = 0;
  matrix->show();
  }

  void MatrixSetup() {
    Serial.begin(9600);

    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
    //matrix->fillScreen(LED_WHITE_HIGH);
    //matrix->show();
    //delay(1000);
    matrix->clear();
    numImage=(sizeof(RGB_bmp) / sizeof(RGB_bmp[0]));
    Serial.print("Number of images: ");
    Serial.println(numImage);
    matrix->fillScreen(LED_BLUE);
    matrix->show();
  }

  void MatrixAlert(){
    // clear the screen after X bitmaps have been displayed and we
    // loop back to the top left corner
    // 8x8 => 1, 16x8 => 2, 17x9 => 6
    static uint8_t pixmap_count = ((mw + 4) / 5) * ((mh + 5) / 6);
    // Cycle through red, green, blue, display 2 checkered patterns
    // useful to debug some screen types and alignment.

    Serial.print("Screen pixmap capacity: ");
    Serial.println(pixmap_count);

    display_rgbBitmap(counter++);
    delay(500);

    if (counter >=numImage){
      counter = 1;
    }

    Serial.println ("----------------------------------------------------------------");
    delay(4000);
  }

  void MatrixStandby(){
    display_rgbBitmap(0);
    matrix->show();
  }
#endif

// Board-specific configurations
#ifdef BOARD_NODEMCU_32S
  #define LED_PIN   13
  #define NUM_LEDS  16
  // Lighting is driven by MQTT messages — no periodic blinking here.

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void alert() {
  theaterChase(strip.Color(255, 0, 0), 100);  //Red, higher brightness
}

void standby() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); // Initialize all pixels to 'white'
  }
  strip.show(); // Update strip to match
}

void LEDsetup() {
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
    // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); // Initialize all pixels to 'white'
  }
  strip.show(); // Update strip to match
}
#endif

#ifdef BOARD_TTGO_T_OI_PLUS
  #define LED_PIN   3
  #define NUM_LEDS  16
  // Lighting is driven by MQTT messages — no periodic blinking here.

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void alert() {
  theaterChase(strip.Color(255, 0, 0), 100);  //Red, higher brightness
}

void standby() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); // Initialize all pixels to 'white'
  }
  strip.show(); // Update strip to match
}

void LEDsetup() {
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
    // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255)); // Initialize all pixels to 'white'
  }
  strip.show(); // Update strip to match
}
#endif