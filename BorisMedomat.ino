// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
//#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"

#define SECOND 1000

// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA, SCL);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h

// Positions are full
int positions[] = {1, 1};
int sum = 0;
int price = 200;

// GPIO coin input
#define COIN_PIN 18
#define DOOR_PIN LED_BUILTIN //19

#define COIN_AMOUNT 2
#define PRICE 200
#define DOOR_TIME 5 * SECOND

// Optionally include custom images
#include "honey.h"

// Main functions
#include "functions.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Begin");
  Serial.println(SDA);
  Serial.println(SCL);

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  pinMode(COIN_PIN, INPUT);
  pinMode(DOOR_PIN, OUTPUT);
  drawImage();
}

void loop() {
  if (digitalRead(COIN_PIN) && !isOutOfStock()) {
    sum += COIN_AMOUNT;
    if (sum >= price) {
      openDoor();
      sum = 0;
    } else {
      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 20, String(sum) + "/" + String(PRICE) + "Eur");
      display.display();
    }
  }
}
