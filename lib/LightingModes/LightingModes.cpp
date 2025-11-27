#include "LightingModes.h"
#include <Arduino.h>
#define LED_PIN    3   //GPIO 3 for ESP32-C3; GPIO 13 for NodeMCU-32S; or any PWM pin

// Lighting is driven by MQTT messages — no periodic blinking here.

void alert() { //PWM alert "soft blink"
  // increase the LED brightness
  for(int i = 0; i <= 150; i++){   
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
  // decrease the LED brightness
  for(int i = 150; i >= 0; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
  // increase the LED brightness
  for(int i = 0; i <= 150; i++){   
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
  // decrease the LED brightness
  for(int i = 150; i >= 0; i--){
    // changing the LED brightness with PWM
    analogWrite(LED_PIN, i);
    delay(15);
  }
}

void standby() {
  analogWrite(LED_PIN, 150); // full brightness LED to indicate standby mode
}

void LEDsetup() {
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 255); // Start with LED on HIGH for 2 seconds
  delay(2000);
  analogWrite(LED_PIN, 150); // then set to standby brightness
}