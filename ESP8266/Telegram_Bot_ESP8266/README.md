# ESP8266 Telegram LED Bot

Simple Telegram bot for ESP8266 that controls an LED over Wi-Fi using the [FastBot](https://github.com/GyverLibs/FastBot) library.

## Features

* Wi-Fi connection
* Telegram bot control
* LED ON/OFF control
* Smooth LED blinking using `sin()`
* Automatic deep sleep on Wi-Fi failure

---

## Libraries

* `Arduino`
* `ESP8266WiFi`
* `FastBot`

---

## Configuration

Create a `config.hpp` file:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Wi-Fi settings
#define SSID "YOUR_WIFI_SSID"
#define PASSWORD "YOUR_WIFI_PASSWORD"

// Telegram bot token
#define BOT_TOKEN "BOT_ID:BOT_SECRET"

// GPIO settings
#define LED_PIN D1

#endif
```

---

## LED Connection

```plain_text
ESP8266 D1 ---> Resistor ---> LED ---> GND
```

---

## Wi-Fi Connection

Function:

```cpp
unsigned char connectToWifi()
```

### Connection Logic

* Starts connection using `WiFi.begin()`
* Maximum connection attempts: `30`
* Delay between attempts:

```txt 
500 ms
```

### Timeout Formula

```txt
attempts * delay
```

### Current Timeout

```txt
30 * 500 ms = 15000 ms = 15 s
```

---

## Smooth LED Blinking

Function:

```cpp
void blinkLed(float tStart, float tIter, float tMax)
```

### Brightness Formula

```cpp
((sin(t) + 1) / 2) * 255
```

### PWM Range

```txt
0 → 255
```

### Blinking Time Formula

```txt
((tMax - tStart) / tIter) * delayMS / 1000
```

### Example

```txt id="y8b5ph"
((50 - 0.01) / 0.05) * 10 / 1000
≈ 9.998 s
```

---

## Telegram Commands

| Command     | Description             |
| ----------- | ----------------------- |
| `/start`    | Show available commands |
| `/on`       | Turn LED ON             |
| `/off`      | Turn LED OFF            |
| `/blinkLed` | Start smooth blinking   |

---

## Main Logic

### setup()

1. Starts Serial communication
2. Configures LED pin
3. Connects to Wi-Fi
4. Attaches Telegram message handler

### loop()

```cpp
bot.tick();
```

Processes incoming Telegram messages continuously.

---

## Deep Sleep

If the Wi-Fi connection fails:

```cpp
ESP.deepSleep(180 * 10000000);
```

### Formula

```txt
seconds * 1 000 000
```

### Current Value

```txt
1800 s = 30 min
```

---

## Supported Boards

* NodeMCU
* Wemos D1 Mini
* ESP8266 boards

---

## Upload

1. Install required libraries
2. Configure `config.hpp`
3. Select ESP8266 board
4. Upload firmware

---

## Example

```txt
/start
-> Hello! Use /on to enable LED and /off to disable it

/on
-> LED turned ON

/blinkLed
-> LED started blinking

/off
-> LED turned OFF
```