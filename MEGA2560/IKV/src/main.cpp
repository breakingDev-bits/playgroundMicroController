#include <Arduino.h>
#include <IRremote.hpp>

#define RECEIVER 2
#define LED 7
#define CONTROL_LED 0x40

bool LedOFF = true;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  IrReceiver.begin(RECEIVER, ENABLE_LED_FEEDBACK); 
  Serial.println("IKV-RECEIVER IS ON");
}

void baseCommand() {
  if (IrReceiver.decodedIRData.command == CONTROL_LED) {
    
    if (LedOFF) {
      digitalWrite(LED, HIGH);
      LedOFF = false;
      return;
    }

    digitalWrite(LED, LOW);
    LedOFF = true;
  }
}


void loop() {
  if (IrReceiver.decode()) {
    if(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      Serial.println("Повтор кнопки...");
    } else {
      baseCommand();
    }
    IrReceiver.resume();
  }
}

void debug() {
  Serial.print("Протокол: ");
  Serial.println(IrReceiver.getProtocolString());
  
  Serial.print("Команда (HEX): 0x");
  Serial.println(IrReceiver.decodedIRData.command, HEX);

  Serial.print("Адрес: 0x");
  Serial.println(IrReceiver.decodedIRData.address, HEX);

}