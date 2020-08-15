void drawPay() {
  display.clear();
  
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Zaplat Zaplat Zaplat Zaplat");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 20, "Zaplat");
  
  display.display();
}

void drawOutOfStock() {
  display.clear();
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 20, ":( :( :(");
  
  display.display();
}

void drawProgressBar() {
  int progress = 0;
  
  for(progress; progress <= 100; progress++) {
    display.clear();
    
    // draw the progress bar
    display.drawProgressBar(0, 5, 120, 10, progress);
  
    // draw the percentage as String
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 30, String(progress) + "%");
    
    display.display();
    delay(DOOR_TIME / 100);
  }
  
}

void drawImage() {
  // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
  // on how to create xbm files
  display.clear();
  display.drawXbm(0, 0, honey_width, honey_height, honey_bits);

  // Write price
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(70, 20, String(8) + "Eur");
  
  display.display();
}

int isOutOfStock() {
  return (positions[door_count - 1] == 0);
}

int openDoor(int pin) {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(door_pins[pin], UNLOCK);

  Serial.println("Open:" + String(pin));
  delay(DOOR_TIME);
  
  digitalWrite(door_pins[pin], LOCK);
  digitalWrite(LED_BUILTIN, LOW);
}

int choosePosition() {

  // Check positions & open right door
  for(int i = 0; i < door_count; i++) {
    
    if (positions[i]) {
      positions[i] = 0; // Empty position
      openDoor(i);      // Open door

      display.clear();
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 20, "Thanks");
      display.display();
      delay(5 * SECOND);

      break;
    }
  }

  // Check last position
  if (isOutOfStock()) {
    Serial.println("Out of stock");
    drawOutOfStock();
  } else {
    drawImage();
  }
  Serial.println("sizeof: " + String(door_count));
}

void readVoltage(int pinNumber = VOLTAGE_PIN)
{
  static const unsigned long REFRESH_INTERVAL = 5 * SECOND; // ms
  static unsigned long lastRefreshTime = 0;
  static const float refVoltage = 3.3;
  static const int resolution = 4096;

  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
	{
		lastRefreshTime += REFRESH_INTERVAL;
    
    // Voltage measurement
    float voltageRaw = analogRead(pinNumber);
    Serial.println(voltageRaw);
    voltageRaw = voltageRaw * (refVoltage / resolution);
    Serial.println("Vout: " + String(voltageRaw));
  
    float voltage = voltageRaw * (R1 + R2) / R2;
    Serial.println("Vin: " + String(voltage));
	}
}
