#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // Try 0x3D if 0x3C doesn't work
#define OLED_RESET -1

const int potpin = 4;  // Use a valid ADC1 pin (32-39)
int potval = 0;
float smoothedVal = 0;  // Use float for smoothing

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 initialization failed"));
    for (;;);
  }

  pinMode(potpin, INPUT);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  potval = analogRead(potpin);  // Read raw potentiometer value
  smoothedVal = (smoothedVal * 0.9) + (potval * 0.1); // Exponential smoothing
  int percentage = map(smoothedVal, 0, 4095, 0, 100); // Scale to 0-100%

  Serial.print("Potentiometer: ");
  Serial.print(potval);
  Serial.print(" -> Smoothed: ");
  Serial.print(smoothedVal);
  Serial.print(" -> Percentage: ");
  Serial.println(percentage);

  display.clearDisplay();
  display.setCursor(10, 20);
  display.print(percentage);
  display.print("%");
  display.display();


}
