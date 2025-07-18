#include <WiFi.h>
#include <ESP32Ping.h>

const char* ssid = "YourWiFiName";
const char* password = "YourWifiPassword";

// Ping test server (Google DNS)
IPAddress pingAddr(8, 8, 8, 8);

#define LED_BUILTIN 2  // Onboard LED for ESP32

void connectToWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int retry = 0;

  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
    Serial.print("Connected SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi Connection Failed!");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  connectToWiFi();
}

void loop() {
  Serial.println("----- Checking Network Status -----");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to SSID: ");
    Serial.println(WiFi.SSID());
    Serial.println("✅ WiFi Connected");

    if (Ping.ping(pingAddr)) {
      Serial.println("✅ Internet is reachable (Ping OK)");
      digitalWrite(LED_BUILTIN, LOW);  // LED off = OK
    } else {
      Serial.println("❌ Internet NOT reachable!");
      blinkLED(2);
    }

  } else {
    Serial.println("❌ WiFi Disconnected!");
    digitalWrite(LED_BUILTIN, HIGH);  // LED on = problem
    connectToWiFi();  // Attempt reconnection
  }

  delay(5000);  // Wait 5 seconds before checking again
}

void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}
