/**
 * @file connection_manager.h
 * @brief Manages WiFi connection modes (ONLINE/OFFLINE)
 */

#pragma once

#include "Arduino.h"

// Connection modes
enum ConnectionMode {
    OFFLINE = 0,
    ONLINE = 1
};

// Connection manager functions
void initializeConnection(ConnectionMode mode);
bool isOnline();
ConnectionMode getConnectionMode();
void setConnectionMode(ConnectionMode mode);
void resetWiFiSettings(); // New function to reset WiFi credentials
void startWiFiConfigPortal(); // New function to start config portal on demand
void clearWiFiCredentials(); // Function to clear WiFi credentials

// LED status functions
void setConnectionStatusLED(bool connected);
void turnOffAllLEDs();

// Global connection state
extern ConnectionMode currentConnectionMode;
extern bool wifiConnected;

// Default status LED pin (override by defining STATUS_LED_PIN before including
// this header, or in a project-wide config). Uses GPIO2 by default which is
// the common built-in LED pin on many ESP32 dev boards.
#ifndef STATUS_LED_PIN
#define STATUS_LED_PIN 2
#endif
