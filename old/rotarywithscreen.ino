#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AiEsp32RotaryEncoder.h>

// --- Screen Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Encoder Pin Definitions ---
#define ENCODER1_A 18
#define ENCODER1_B 19
#define ENCODER2_A 5
#define ENCODER2_B 23
#define ENCODER3_A 16
#define ENCODER3_B 17

// --- Encoder Value Range ---
#define MIN_VALUE 0
#define MAX_VALUE 100

// --- Create Encoder Objects ---
AiEsp32RotaryEncoder encoder1(ENCODER1_A, ENCODER1_B, -1, -1, 4);
AiEsp32RotaryEncoder encoder2(ENCODER2_A, ENCODER2_B, -1, -1, 4);
AiEsp32RotaryEncoder encoder3(ENCODER3_A, ENCODER3_B, -1, -1, 4);

// --- Interrupt Service Routines ---
void IRAM_ATTR handleEncoder1() { encoder1.readEncoder_ISR(); }
void IRAM_ATTR handleEncoder2() { encoder2.readEncoder_ISR(); }
void IRAM_ATTR handleEncoder3() { encoder3.readEncoder_ISR(); }

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow time for Serial Monitor

  // Initialize encoder pins with internal pull-ups
  pinMode(ENCODER1_A, INPUT_PULLUP);
  pinMode(ENCODER1_B, INPUT_PULLUP);
  pinMode(ENCODER2_A, INPUT_PULLUP);
  pinMode(ENCODER2_B, INPUT_PULLUP);
  pinMode(ENCODER3_A, INPUT_PULLUP);
  pinMode(ENCODER3_B, INPUT_PULLUP);

  // Begin and configure the encoders
  encoder1.begin();
  encoder2.begin();
  encoder3.begin();
  encoder1.setup(handleEncoder1);
  encoder2.setup(handleEncoder2);
  encoder3.setup(handleEncoder3);

  // Set boundaries and acceleration for each encoder
  encoder1.setBoundaries(MIN_VALUE, MAX_VALUE, true);
  encoder2.setBoundaries(MIN_VALUE, MAX_VALUE, true);
  encoder3.setBoundaries(MIN_VALUE, MAX_VALUE, true);
  encoder1.setAcceleration(20);
  encoder2.setAcceleration(20);
  encoder3.setAcceleration(20);

  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
}

void loop() {
  // Read current values from all three encoders
  int value1 = encoder1.readEncoder();
  int value2 = encoder2.readEncoder();
  int value3 = encoder3.readEncoder();

  // Clear display before drawing new content
  display.clearDisplay();

  // Define vertical offsets for each encoder section
  int offset1 = 0;   // Section 1: rows 0 - 20
  int offset2 = 21;  // Section 2: rows 21 - 41
  int offset3 = 42;  // Section 3: rows 42 - 63

  // --- Draw Encoder 1 ---
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, offset1);
  display.print("Encoder 1: ");
  display.print(value1);
  int barWidth1 = map(value1, MIN_VALUE, MAX_VALUE, 0, SCREEN_WIDTH);
  display.drawRect(0, offset1 + 10, SCREEN_WIDTH, 5, SSD1306_WHITE);
  display.fillRect(0, offset1 + 10, barWidth1, 5, SSD1306_WHITE);

  // --- Draw Encoder 2 ---
  display.setCursor(0, offset2);
  display.print("Encoder 2: ");
  display.print(value2);
  int barWidth2 = map(value2, MIN_VALUE, MAX_VALUE, 0, SCREEN_WIDTH);
  display.drawRect(0, offset2 + 10, SCREEN_WIDTH, 5, SSD1306_WHITE);
  display.fillRect(0, offset2 + 10, barWidth2, 5, SSD1306_WHITE);

  // --- Draw Encoder 3 ---
  display.setCursor(0, offset3);
  display.print("Encoder 3: ");
  display.print(value3);
  int barWidth3 = map(value3, MIN_VALUE, MAX_VALUE, 0, SCREEN_WIDTH);
  display.drawRect(0, offset3 + 10, SCREEN_WIDTH, 5, SSD1306_WHITE);
  display.fillRect(0, offset3 + 10, barWidth3, 5, SSD1306_WHITE);

  // Refresh the display
  display.display();

  // Debug: Print encoder values to Serial Monitor
  Serial.printf("Enc1: %d, Enc2: %d, Enc3: %d\n", value1, value2, value3);
  delay(50); // Small delay to smooth display updates
}
