# ESP8266 LED Web Controller

Simple HTTP server for ESP8266 that allows controlling an LED from a web browser.

## Features

* Wi-Fi connection
* Embedded HTTP server
* LED control via browser
* Minimal memory usage (Maybe. But I try it)
* Simple REST-like routes

## Hardware

* ESP8266 board
* LED connected to `D2`

## Libraries

* `ESP8266WiFi`
* `ESP8266WebServer`

## Configuration

Set your Wi-Fi credentials:

```cpp
#define SSID "YOUR_WIFI"
#define PASSWORD "YOUR_PASSWORD"
```

Set LED pin:

```cpp
#define LED_PIN D2
```

## Routes

| Route      | Description   |
| ---------- | ------------- |
| `/`        | Main web page |
| `/led/on`  | Turn LED on   |
| `/led/off` | Turn LED off  |

## Usage

1. Upload firmware to ESP8266
2. Open Serial Monitor (`115200 baud`)
3. Get local IP address
4. Open ESP8266 IP in browser
5. Control LED using buttons

## Example

```text
http://192.168.1.15
```

## Notes

* HTML is stored directly in flash memory using `F()`
* Designed for low RAM usage
* Uses synchronous request handling with `handleClient()`

## Serial Output

```text
Подключение к Wi-Fi
-#-#-#
Успешно подключился.
IP-адрес: 192.168.x.x

HTTP сервер запущен
```
