#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// #include "config.h"
#include "myConfig.h"

ESP8266WebServer server(80);

void wifiConnect() {
  WiFi.begin(SSID, PASSWORD);
  Serial.println("");
  Serial.print("Подключение к Wi-Fi\n");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print("-#");
  }

  Serial.println("");
  Serial.println("Успешно подключился. ");
  Serial.print("IP-адрес: ");
  Serial.println(WiFi.localIP());
}

void routerRoot() {
  server.send(200, "text/html; charset=utf-8", F("<h1>On the LED please:3</h1> <button onclick='fetch(\"/led/on\")'>LED ON</button> <button onclick='fetch(\"/led/off\")'>LED OFF</button>"));
}

void OnTheLed() {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain; charset=utf-8", "OK");
}

void OffTheLed() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain; charset=utf-8", "OK");
}

void routerNotFound() {
  server.send(404, "text/html; charset=utf-8", "<h1>Where do u going?</h1>");
}

void webServer() {
  server.on("/", routerRoot);
  server.on("/led/on", OnTheLed);
  server.on("/led/off", OffTheLed);
  server.onNotFound(routerNotFound);

  server.begin();
  Serial.println("HTTP сервер запущен");
}

void setup() { 
  Serial.begin(115200); 
  delay(10);
  pinMode(LED_PIN, OUTPUT);

  wifiConnect();
  webServer();
}

void loop() {  
  server.handleClient();
}