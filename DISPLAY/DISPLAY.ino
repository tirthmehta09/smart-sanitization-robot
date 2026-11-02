#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>   // Add this line for a smoother font

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create I2C object with custom pins
TwoWire myWire = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, -1);

void setup() {
  Serial.begin(115200);

  // Start I2C with custom pins (SDA=12, SCL=14)
  myWire.begin(21, 22);

  // Initialize OLED at address 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Stop if display not found
  }

  // Clear display
  display.clearDisplay();

  // Use custom font
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 30);  // Adjust Y so text isn’t cut off
  display.println("Hello Tirth!");
  display.display();         // Show it on screen
}

void loop() {
  // Nothing here, text stays on screen
}
