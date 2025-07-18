##  Captive Portal Wi-Fi configuration

Integrate ***WiFiManager***, so it supports Captive Portal Wi-Fi configuration on first boot or when Wi-Fi credentials are missing.

## ✅ What We’ll Get:

- ESP32 boots up → no Wi-Fi?
- Starts a hotspot (e.g., ESP32-Setup)
- Shows a web portal for Wi-Fi setup
- Stores Wi-Fi credentials in flash (non-volatile)
- Automatically connects on future boots
- Falls back to portal if credentials fail

## 📦 Install WiFiManager Library

- Open Arduino IDE
- Go to Sketch > Include Library > Manage Libraries
- Search for WiFiManager by tzapu
- Click Install

- Also make sure your ESP32 board package is up-to-date via Tools > Board > Board Manager.

## 🛠️ Code

```
#include <WiFi.h>
#include <ESP32Ping.h>
#include <WiFiManager.h>  // Add this

#define LED_BUILTIN 2
IPAddress pingAddr(8, 8, 8, 8); // Google DNS

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Start WiFiManager
  WiFiManager wm;

  // Optional: Reset saved Wi-Fi credentials for testing
  // wm.resetSettings();

  // Automatically connect to saved network or start portal
  if (!wm.autoConnect("DownDetect")) {
    Serial.println("❌ Failed to connect and no portal configured");
    ESP.restart();
    delay(1000);
  }

  Serial.println("✅ Connected to Wi-Fi!");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("----- Checking Network Status -----");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to SSID: ");
    Serial.println(WiFi.SSID());
    Serial.println("✅ WiFi Connected");

    if (Ping.ping(pingAddr)) {
      Serial.println("✅ Internet is reachable (Ping OK)");
      digitalWrite(LED_BUILTIN, LOW);  // LED off
    } else {
      Serial.println("❌ Internet NOT reachable!");
      blinkLED(2);
    }

  } else {
    Serial.println("❌ WiFi Disconnected!");
    digitalWrite(LED_BUILTIN, HIGH);  // LED on
  }

  delay(5000); // Check every 5 seconds
}

void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}

```

## 💡 What Happens Now?

- Scenario Behavior
  - First boot or Wi-Fi credentials missing : Starts AP mode: DownDetect
  - Device connects successfully : Saves SSID/pass and reuses them automatically
  - Wi-Fi fails later : LED stays ON, shows error on Serial
  - Internet unreachable : LED blinks and logs ping failure

## 🧪 To Test Captive Portal

- Upload the code
- On first boot, ESP32 will create a Wi-Fi: DownDetect
- Connect to it with your phone/laptop
- Browser will redirect to a config page
- Enter your Wi-Fi SSID and password
- ESP32 will reboot and connect automatically

- You can reset credentials by uncommenting wm.resetSettings(); temporarily.