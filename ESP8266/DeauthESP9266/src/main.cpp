#include <Arduino.h>
#include <ESP8266WiFi.h>

void sniffer(uint8_t *buf, uint16_t len) {
  // Easys sniffer
  Serial.print("Pkg, len: ");
  Serial.println(len);
}

void ToMonitorMode(void (*sniffer)(uint8_t*, uint16_t)) {
  WiFi.mode(WIFI_STA); // To client mode

  wifi_promiscuous_enable(0); // Close promiscuous mode
  wifi_set_promiscuous_rx_cb(sniffer); // Set promiscuous function and enable promiscuous mode 
  wifi_promiscuous_enable(1);
  
  Serial.println("ESP8266 in monitor mode");
}

void setup() {  
  Serial.begin(115200);
  Serial.println("\nESP8266 start");


  ToMonitorMode(sniffer);
}

void loop() {

}