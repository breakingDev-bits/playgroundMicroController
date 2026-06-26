#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FastBot.h>
#include "myConfig.hpp"
// #include "config.hpp"

FastBot bot(BOT_TOKEN);

unsigned char connectToWifi() {  
    unsigned char tries = 225; 
    // 255 - 225 = 30 * 500 MS = 15.000 / 1000 = 15~ Second
    WiFi.begin(SSID, PASSWORD);
    Serial.print("\nTry connect to ");
    Serial.print(SSID);
    Serial.print("...\n#");

    while (WiFi.status() != WL_CONNECTED && tries != 0) {
        delay(500);
        Serial.print("-#");
        tries = tries + 1;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("\nCan't connect to WIFI, check the password\n");
        goto err;
    }

    Serial.print("\nSuccesfull connect to ");
    Serial.print(SSID);
    Serial.print("!\n");
    return 1;


    err:
        return 0;
}
// Blinking time formula: ((tMax - tStart) / tIter) * delayMS / 1000 = Seconds
// Example: ((50 - 0.05) / 0.1) * 10 / 1000 = 4.995 S
void blinkLed(float tStart, float tIter, float tMax) {
    while(tStart < tMax) {
        tStart += tIter;

        float blink = ((sin(tStart) + 1) / 2) * 255;
        analogWrite(LED_PIN, blink);

        delay(10);
    }

    analogWrite(LED_PIN, 0); // Reset   
}

void newMsg(FB_msg& msgFromBot) {
    if (msgFromBot.text == "/start") {
        bot.sendMessage("Привет! Используй /on для включения и /off для выключения", msgFromBot.userID);
    } 
    else if (msgFromBot.text == "/on") {
        digitalWrite(LED_PIN, HIGH);
        bot.sendMessage("Светодиод включился!", msgFromBot.userID);
    } 
    else if (msgFromBot.text == "/blinkLed") {
        bot.sendMessage("Светодиод начал бликать!", msgFromBot.userID);
        blinkLed(0.01, 0.05, 50);
    }
    else if (msgFromBot.text == "/off") {
        digitalWrite(LED_PIN, LOW);
        bot.sendMessage("Светодиод выключился!", msgFromBot.userID);
    }
}

void cleanUpLoaderTrash() {
    for(unsigned char index = 0; index < 20; index++) Serial.print("\n");
}

void setup() {
    Serial.begin(115200);
    cleanUpLoaderTrash();
    pinMode(LED_PIN, OUTPUT);
    
    if(!connectToWifi()) {
        while(1) {
            Serial.print("In deepSleep");
            ESP.deepSleep(180 * 10000000);
        }
    }

    // else
    bot.attach(newMsg);
}

void loop() {
    bot.tick();
}
