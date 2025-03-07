#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ctrl.h> // Include the Ctrl library to handle rotary encoders

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // Try 0x3D if 0x3C doesn't work
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Initialize rotary encoder (only one encoder for now)
Ctrl encoder1(2, 3); // Encoder 1: Pins 2 (A) and 3 (B)

// Variables to store encoder values (initially set to 50, range 0-100)
int value1 = 50; // Initial value for the first encoder

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 initialization failed"));
    for (;;); // Loop forever if initialization fails
  }
}

void loop() {
  // Handle the encoder and update its value
  handleEncoder(encoder1, value1, "Encoder 1");

  // Calculate the bar width based on the encoder value (0-100)
  int barWidth = map(value1, 0, 100, 0, SCREEN_WIDTH - 20);

  display.clearDisplay(); // Clear the display

  // Display static text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 5);
  display.print("Mode 1");

  // Draw the outline of the bar
  display.drawRect(10, 30, SCREEN_WIDTH - 20, 20, SSD1306_WHITE);

  // Draw the filled bar based on the encoder value
  display.fillRect(10, 30, barWidth, 20, SSD1306_WHITE);

  // Update the display
  display.display();
}

// Function to handle the encoder, update its value, and print to Serial
void handleEncoder(Ctrl &encoder, int &value, const char *label) {
  int change = encoder.change(); // Get the encoder movement (+1 or -1)
  if (change) { // Only update if there is movement
    value = constrain(value + change, 0, 100); // Ensure the value stays between 0 and 100
  }
}
