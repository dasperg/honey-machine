// Board: "DOIT ESP32 DEVKIT V1"

// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include "WiFi.h"

// Main configuration
#include "config.h"
int config();
int positions[] = {1, 1};
int door_pins[] = {25, 26};
int door_count = sizeof(door_pins)/sizeof(int);

int balance = 0;
int price = 8;

// Optionally include custom images
#include "honey.h"

// Initialize the OLED display using Arduino Wire:
// ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h
SSD1306Wire display(DISPLAY_ADDR, SDA, SCL);

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

  pinMode(COIN_PIN, INPUT_PULLUP);

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // Wait for capacitor, 
  // opening doors comsume lot of current
  delay(5 * SECOND);

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
  readVoltage();
  
  if (coin && !isOutOfStock()) {
    balance += COIN_AMOUNT;

    Serial.println(balance);
    
    if (balance >= price) {
      choosePosition();
      balance = 0;
    } else {

      // Display price
      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 20, String(balance) + "/" + String(price) + "Eur");
      display.display();
    }
  }
}
