#include "LightingModes.h"
#include <Arduino.h>
#define LED_PIN    13   //GPIO 3 for ESP32-C3; GPIO 13 for NodeMCU-32S; or any PWM pin

// Lighting is driven by MQTT messages — no periodic blinking here.

void alert() { //PWM alert "soft blink"
  pinMode(LED_PIN, OUTPUT);
  for(int i = 10; i >= 255; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(1);
  }
// decrease the LED brightness
  for(int i = 255; i >= 0; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(1);
  }
  for(int i = 0; i >= 255; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(1);
  }
  // decrease the LED brightness
  for(int i = 255; i >= 0; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(1);
  }
    for(int i = 0; i >= 255; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(1);
  }
  // decrease the LED brightness
  for(int i = 255; i >= 10; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(1);
  }
}

void alert2() { //PWM alert "soft blink"
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 255); // keep LED at full brightness for a moment  pinMode(LED_PIN, OUTPUT);
  for(int i = 10; i >= 255; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
  // decrease the LED brightness
  for(int i = 255; i >= 0; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
    for(int i = 0; i >= 255; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
  // decrease the LED brightness
  for(int i = 255; i >= 10; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
}

void standby() {
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 10); // full brightness LED to indicate standby mode
}

void LEDsetup() {
  pinMode(LED_PIN, OUTPUT);
  for(int i = 0; i >= 255; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
  // decrease the LED brightness
  for(int i = 255; i >= 10; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
}
