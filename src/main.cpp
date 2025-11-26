#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <LightingModes.h> //MODIFIED
#include <../lib/Managers/connection_manager.h>
#include <../lib/Managers/mqtt_manager.h>
#include <esp_task_wdt.h>

void setup() {
  // Initialise serial (optional)
  Serial.begin(9600);
  delay(10);
  
  LEDsetup();

  // Initialize connection manager (ONLINE mode)
  initializeConnection(ONLINE);
  Serial.println("Connection manager initialized.");

  // Initialize MQTT manager
  mqttManager_begin();
  Serial.println("MQTT Manager started.");
  standby(); //turn on LEDs in standby mode
}

void loop() {
  // Reset watchdog to prevent timeout
  esp_task_wdt_reset();
  
  // Run MQTT manager loop (handles reconnects and incoming messages)
  mqttManager_loop();
  
  // Give other tasks some CPU time
  delay(10);
}