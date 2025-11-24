/**
 * @file connection_manager.cpp
 * @brief Manages WiFi connection (ONLINE only). Uses WiFiManager as a
 * fallback config portal when no stored credentials are available.
 */

#include "connection_manager.h"

// Use WiFiManager instead of secrets.h for runtime configuration
#include <WiFi.h>
#include <WiFiManager.h> // tzapu/WiFiManager
#include <ESPmDNS.h>
#include <esp_task_wdt.h>

// Global connection state (force online mode)
ConnectionMode currentConnectionMode = ONLINE;
bool wifiConnected = false;

// Track if WDT is initialized
static bool wdtInitialized = false;

// Internal helper: launch WiFiManager portal (blocks until configured or timeout)
static void startWiFiConfigPortalImpl() {
    const char* apName = "aninipot";
    Serial.println("=== CONFIG PORTAL (AP mode) ===");
    Serial.print("AP SSID: ");
    Serial.println(apName);
    Serial.println("Connect a phone or laptop to this AP and open http://192.168.4.1 to configure Wi‑Fi");

    WiFi.mode(WIFI_AP_STA); // keep STA available while hosting AP
    WiFiManager wm;
    // Optionally set a portal timeout: wm.setTimeout(300); // seconds

    bool res = wm.autoConnect(apName);
    if (res) {
        Serial.println("WiFiManager: credentials saved and device attempted to connect to the configured network.");
    } else {
        Serial.println("WiFiManager: failed or timed out (returning to application).");
    }
}

/**
 * @brief Initialize connection in ONLINE mode only
 *
 * Behavior:
 * - Attempt to connect using stored credentials (WiFi.begin()).
 * - If that fails within the timeout, launch WiFiManager config portal
 *   (AP SSID: "ghostwhisper") which blocks until credentials are
 *   provided (or WiFiManager times out if configured). After portal
 *   returns we re-check connectivity and start mDNS if connected.
 */
void initializeConnection(ConnectionMode mode) {
    (void)mode; // ignore requested mode; system is online-only
    currentConnectionMode = ONLINE;

    delay(1000);
    Serial.println("");
    Serial.println("==================================================");


    // Status LED
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    // Initialize watchdog ONCE at startup (30s timeout, panic on trigger)
    if (!wdtInitialized) {
        esp_task_wdt_init(30, true);
        esp_task_wdt_add(NULL); // add loop task once
        wdtInitialized = true;
        Serial.println("Watchdog initialized (30s timeout)");
    }

    // Attempt to connect using stored credentials first
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(false); // keep stored credentials
    delay(100);

    Serial.println("Attempting WiFi connect using stored credentials (if any)...");
    WiFi.begin(); // try previously saved credentials

    // Wait for connection (~15s)
    int attempts = 0;
    const int maxAttempts = 30;
    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        // feed watchdog while blocking
        esp_task_wdt_reset();
        delay(500);
        Serial.print('.');
        attempts++;
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        wifiConnected = true;
        setConnectionStatusLED(true);

        Serial.println("=== STA MODE (connected) ===");
        Serial.print("Assigned IP address: ");
        Serial.println(WiFi.localIP());

        // Optionally start/announce mDNS if enabled in config
#if ENABLE_MDNS
        if (MDNS.begin("ghostwhisper")) {
            MDNS.addService("http", "tcp", 80);
            Serial.println("mDNS responder started (ghostwhisper.local).");
        }
#endif
    } else {
        // No stored creds or failed -> launch WiFiManager portal (blocks until done)
        wifiConnected = false;
        setConnectionStatusLED(false);
        Serial.println("No stored WiFi or connect timed out. Launching config portal...");

        startWiFiConfigPortalImpl();

        // After portal returns, check connection
        if (WiFi.status() == WL_CONNECTED) {
            wifiConnected = true;
            setConnectionStatusLED(true);

            Serial.println("=== STA MODE (connected) ===");
            Serial.print("Assigned IP address: ");
            Serial.println(WiFi.localIP());

            // Optionally start/announce mDNS if enabled in config
#if ENABLE_MDNS
            if (MDNS.begin("aninipot")) {
                MDNS.addService("http", "tcp", 80);
                Serial.println("mDNS responder started (aninipot.local).");
            }
#endif
        } else {
            Serial.println("Still not connected after config portal. Restarting device.");
            delay(2000);
            ESP.restart();
        }
    }

    Serial.println("==================================================");
    Serial.println("Connection initialization complete.");
}

/**
 * @brief Check if the device is connected to WiFi
 */
bool isOnline() {
    return (currentConnectionMode == ONLINE && wifiConnected);
}

/**
 * @brief Get the current connection mode
 */
ConnectionMode getConnectionMode() {
    return currentConnectionMode;
}

/**
 * @brief Set the connection mode (no-op: system is online-only)
 */
void setConnectionMode(ConnectionMode mode) {
    // System is configured as online-only. Ignore requested mode but keep API
    // compatibility by ensuring the global remains ONLINE.
    (void)mode;
    currentConnectionMode = ONLINE;
}

/**
 * @brief Set the connection status LED
 */
void setConnectionStatusLED(bool connected) {
    if (connected) {
        digitalWrite(STATUS_LED_PIN, HIGH); // solid ON
    } else {
        digitalWrite(STATUS_LED_PIN, LOW);
    }
}

/**
 * @brief Turn off all status LEDs
 */
void turnOffAllLEDs() {
    digitalWrite(STATUS_LED_PIN, LOW);
}

/**
 * @brief Reset WiFi settings - clears WiFiManager stored creds and WiFi stack
 */
void resetWiFiSettings() {
    Serial.println("resetWiFiSettings() called - clearing WiFiManager settings and WiFi stack");
    WiFiManager wm;
    wm.resetSettings();
    WiFi.disconnect(true); // remove stored credentials from WiFi stack
}

/**
 * @brief Start WiFi config portal (public wrapper)
 */
void startWiFiConfigPortal() {
    startWiFiConfigPortalImpl();
}

/**
 * @brief Clear WiFi credentials - wrapper around reset
 */
void clearWiFiCredentials() {
    resetWiFiSettings();
}
