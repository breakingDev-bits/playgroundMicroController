#include <Arduino.h>
#include <math.h>

#define LED_PIN 2

float timeX = 0.1f; 
float timeY = 0.1f;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); 
}

void loop() {
  float bright = ((cosf(timeX) - sinf(timeY)) + 1) / 2;
  timeX = timeX + 0.1f;
  timeY += 0.05f + (sinf(bright) * 0.2f);
  bright *= 255.0f; 

  if (random(100) < 1) {
    float glitch = (float)random(-10, 10) * 0.05f;
    timeX += glitch; 
  }

  analogWrite(LED_PIN, (int)bright);
  delay(50);
}