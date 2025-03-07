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
#define ENCODER2_A 2
#define ENCODER2_B 4

// --- Encoder Value Range ---
#define MIN_VALUE 0
#define MAX_VALUE 100

// --- Create Encoder Objects ---
AiEsp32RotaryEncoder encoder1(ENCODER1_A, ENCODER1_B, -1, -1, 4);
AiEsp32RotaryEncoder encoder2(ENCODER2_A, ENCODER2_B, -1, -1, 4);

// --- Interrupt Service Routines ---
void IRAM_ATTR handleEncoder1() { encoder1.readEncoder_ISR(); }
void IRAM_ATTR handleEncoder2() { encoder2.readEncoder_ISR(); }

// Global variables to hold the last read values and the active encoder
int activeEncoder = 1;       // 1 = Encoder 1, 2 = Encoder 2
int lastValue1 = MIN_VALUE;  // Last value for Encoder 1
int lastValue2 = MIN_VALUE;  // Last value for Encoder 2

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow time for Serial Monitor

  // Initialize encoder pins with internal pull-ups
  pinMode(ENCODER1_A, INPUT_PULLUP);
  pinMode(ENCODER1_B, INPUT_PULLUP);
  pinMode(ENCODER2_A, INPUT_PULLUP);
  pinMode(ENCODER2_B, INPUT_PULLUP);

  // Begin encoder operation and attach ISRs
  encoder1.begin();
  encoder2.begin();
  encoder1.setup(handleEncoder1);
  encoder2.setup(handleEncoder2);

  // Set boundaries and acceleration
  encoder1.setBoundaries(MIN_VALUE, MAX_VALUE, true);
  encoder2.setBoundaries(MIN_VALUE, MAX_VALUE, true);
  encoder1.setAcceleration(20);
  encoder2.setAcceleration(20);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();

  // Read initial encoder values
  lastValue1 = encoder1.readEncoder();
  lastValue2 = encoder2.readEncoder();
}

void loop() {
  // Check for changes on Encoder 1 and update its value
  if (encoder1.encoderChanged()) {
    lastValue1 = encoder1.readEncoder();
    activeEncoder = 1;
  }
  // Check for changes on Encoder 2 and update its value
  if (encoder2.encoderChanged()) {
    lastValue2 = encoder2.readEncoder();
    activeEncoder = 2;
  }

  // Determine which encoder is active and set the active value and label
  int activeValue;
  String encoderName;
  if (activeEncoder == 1) {
    activeValue = lastValue1;
    encoderName = "Encoder 1";
  } else {
    activeValue = lastValue2;
    encoderName = "Encoder 2";
  }

  // Map the encoder value to a progress bar width
  int barWidth = map(activeValue, MIN_VALUE, MAX_VALUE, 0, SCREEN_WIDTH - 20);

  // Clear the display and draw the active encoder info
  display.clearDisplay();

  // Display the encoder label at the top
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 5);
  display.print(encoderName);

  // Draw the progress bar outline
  display.drawRect(10, 30, SCREEN_WIDTH - 20, 20, SSD1306_WHITE);
  // Fill the progress bar according to the active value
  display.fillRect(10, 30, barWidth, 20, SSD1306_WHITE);

  // Display the numeric value at the bottom
  display.setTextSize(2);
  display.setCursor(35, 55);
  display.print(activeValue);

  display.display();

  // Debug print to Serial Monitor
  Serial.printf("%s value: %d\n", encoderName.c_str(), activeValue);

  delay(50); // Small delay to smooth the display updates
}
