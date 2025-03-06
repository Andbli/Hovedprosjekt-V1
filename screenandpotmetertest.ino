#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // Try 0x3D if 0x3C doesn't work
#define OLED_RESET -1

const int potpin = 4;  // Use ADC1 pin (32-39) to avoid Wi-Fi issues
int potval = 0;
float smoothedVal = 0;  // Smoothing filter

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 initialization failed"));
    for (;;);
  }

  pinMode(potpin, INPUT);
}

void loop() {
  potval = analogRead(potpin);  // Read raw potentiometer value
  smoothedVal = (smoothedVal * 0.9) + (potval * 0.1); // Exponential smoothing
  int percentage = map(smoothedVal, 0, 4095, 0, 101); // Scale to 0-100%
  int barWidth = map(percentage, 0, 100, 0, SCREEN_WIDTH - 20); // Bar width mapping

  Serial.print("Potentiometer: ");
  Serial.print(potval);
  Serial.print(" -> Smoothed: ");
  Serial.print(smoothedVal);
  Serial.print(" -> Percentage: ");
  Serial.println(percentage);

  display.clearDisplay();

  // Display percentage text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 5);
  display.print("Mode 1");

  // Draw bar outline
  display.drawRect(10, 30, SCREEN_WIDTH - 20, 20, SSD1306_WHITE);

  // Draw filled bar
  display.fillRect(10, 30, barWidth, 20, SSD1306_WHITE);

  display.display();

}
