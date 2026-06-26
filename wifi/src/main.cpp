#include <Arduino.h>
#include <WiFi.h>
#include <math.h>

#define SSID "TP-Link_E9F0"
#define PASS "kTWq4BPB"

void connectToWifi() {
    WiFi.begin(SSID, PASS);
    Serial.print("Connecting to WiFi\r\n");

    while(true){
      if(WiFi.status() != WL_CONNECTED) {Serial.print("."); delay(500);} 
      else break;
    }

    Serial.println("\nWiFi connect");
}

void clearConsole() {
  unsigned char i = 1;

  while(i != 30) {
    i += 1;
    Serial.println("");
  }
}

void systemInit(){
  Serial.begin(115200);
  delay(1000);
  clearConsole();

  connectToWifi();
}

void setup() {  
  systemInit();
  Serial.println("ESP32 was initialization");
}

void loop() { }
