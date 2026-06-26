#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT); // Наш щуп
}

void loop() {
  int rawValue = analogRead(A0);

  // Форматируем вывод специально для твоего плоттера
  Serial.print(">Signal:");
  Serial.println(rawValue);
    
  delay(100); // Чуть быстрее обновляем график для отзывчивости
}