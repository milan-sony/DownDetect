# 📡 DownDetect

**DownDetect** is a lightweight Wi-Fi and Internet monitoring tool built using an ESP32 DEVKIT V1 board. It continuously checks whether the device is connected to a Wi-Fi network and whether the internet is reachable (via ping), providing real-time feedback using the onboard LED and Serial Monitor.

## 🧠 Features

- ✅ Connects to specified Wi-Fi network
- 📶 Checks Wi-Fi connection status every 5 seconds
- 🌐 Pings Google DNS (8.8.8.8) to verify internet connectivity
- 🔴 Blinks onboard LED if internet is down
- 🔁 Reconnects automatically if Wi-Fi is disconnected
- 🖨️ Logs SSID and IP address over Serial Monitor
- 💡 Onboard LED Status:
  - LED **OFF** = Wi-Fi and Internet OK
  - LED **Blinking** = Internet not reachable
  - LED **ON** = Wi-Fi disconnected

## ⚙️ Hardware Required

- [x] ESP32 DEVKIT V1
- [x] Micro USB cable
- [ ] Optionally: OLED display, buzzer, or SD card for future features

## 📥 Library Dependencies

Make sure the following libraries are installed in the Arduino IDE:

- `WiFi.h` (comes with ESP32 board support)
- `ESP32Ping.h`  
  📦 Install via Arduino IDE:  
  `Sketch > Include Library > Manage Libraries > Search "ESP32Ping" > Install`
  - If the Library Manager doesn’t show ESP32Ping, you can install it manually: checkout this [link](https://www.dfrobot.com/blog-1411.html?srsltid=AfmBOorOVuO_Zi6C25oXe5YApub4J2_B_4nCw63y4_OR5ALnmk9xciww)

## 📦 Getting Started

1. **Clone or download** this repository.
2. **Open the code** in the Arduino IDE.
3. Install **ESP32 board support** (if not already done):
   - Go to **File > Preferences**
   - Add this URL in "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Then go to **Tools > Board > Board Manager** and install **esp32 by Espressif Systems**.
4. **Update Wi-Fi credentials**:
   ```cpp
   const char* ssid = "YourWiFiName";
   const char* password = "YourWiFiPassword";
5. Select board: Tools > Board > ESP32 Dev Module
6. Upload the code to your ESP32
7. Open Serial Monitor (baud rate: 115200) to see live logs

## 🔁 Main Loop Behavior

```
----- Checking Network Status -----

Connected to SSID: YourWiFiName

✅ WiFi Connected

✅ Internet is reachable (Ping OK)

(OR)

----- Checking Network Status -----

✅ WiFi Connected

❌ Internet NOT reachable!

[LED blinks 2x]

(OR)

❌ WiFi Disconnected!

[LED stays ON]

Reconnecting to WiFi...

```

## 🚀 Future Enhancements

- 📲 Push alerts via Telegram or Webhooks
- 🖥️ OLED display showing network status
- 💾 Log outages to SD card or SPIFFS
- 🔔 Buzzer alert on outage
- 📊 Uptime analytics dashboard with web UI
- 🔒 Captive Portal Wi-Fi configuration
