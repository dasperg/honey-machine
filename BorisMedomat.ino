// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
//#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include "WiFi.h"
//#include <esp_wifi.h>
//#include "esp_deep_sleep.h"

#define SECOND 1000

// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA, SCL);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h

// Positions are full
int positions[] = {1, 1};
int sum = 0;
int price = 100;

// GPIO coin input
#define COIN_PIN 18

int door_pins[] = {25, 26};
int door_count = sizeof(door_pins)/sizeof(int);

#define LOCK HIGH
#define UNLOCK LOW 

#define COIN_AMOUNT 2
//#define PRICE 200
#define DOOR_TIME 0.1 * SECOND

// How many minutes the ESP should sleep
#define DEEP_SLEEP_TIME 1

// Optionally include custom images
#include "honey.h"

// Main functions
#include "functions.h"

void setup() {
  // Debug
  Serial.begin(115200);
  Serial.println("Begin");
  Serial.println(SDA);
  Serial.println(SCL);

  // Save battery
  setCpuFrequencyMhz(80);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  btStop();

  // Deep sleep
  // Configure the timer to wake us up!
//  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME * 60L * 1000000L);

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // IO
  pinMode(COIN_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < door_count; i++) {
    Serial.println(i);

    pinMode(door_pins[i], OUTPUT);
    
    openDoor(i);
  }
  
  drawImage();

  // Go to sleep! Zzzz
//  esp_deep_sleep_start();
}

void loop() {
  int coin = digitalRead(COIN_PIN);
//  Serial.println(coin);
  
  if (coin && !isOutOfStock()) {
    sum += COIN_AMOUNT;

    Serial.println(sum);
    
    if (sum >= price) {
      choosePosition();
      sum = 0;
    } else {
      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 20, String(sum) + "/" + String(price) + "Eur");
      display.display();
    }
  }
}
