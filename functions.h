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
  return (positions[0] == 0 && positions[1] == 0);
}

int openDoor() {
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 20, "Thanks");
  display.display();

  // Check positions & open right door
  if (positions[0]) {
    positions[0] = 0;
    digitalWrite(DOOR_PIN, HIGH);
    drawProgressBar();
    digitalWrite(DOOR_PIN, LOW);
  } else if (positions[1]) {
    positions[1] = 0;
    digitalWrite(DOOR_PIN, HIGH);
    drawProgressBar();
    digitalWrite(DOOR_PIN, LOW);
  }

  if (isOutOfStock()) {
    drawOutOfStock();
  } else {
    drawImage();
  }
}
