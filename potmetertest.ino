#include <RotaryEncoder.h>

// Define rotary encoder pins
#define ROTARY_ENCODER_CLK 18   // CLK pin
#define ROTARY_ENCODER_DT 19    // DT pin

// Create a RotaryEncoder object
RotaryEncoder encoder(ROTARY_ENCODER_CLK, ROTARY_ENCODER_DT);

// Initialize the value variable
int rotval1 = 50;  // Initial value (start in the middle)

void setup() {
  Serial.begin(115200);   // Initialize serial communication
  encoder.begin();        // Initialize the encoder
}

void loop() {
  encoder.tick();  // Update the encoder state

  // Get the current encoder position
  int encoderValue = encoder.getPosition();

  // Map the encoder position to the range 0-100
  rotval1 = map(encoderValue, 0, 1000, 0, 100);  // Assuming the encoder has 1000 steps (adjust accordingly)

  // Ensure the value stays within 0-100 range
  rotval1 = constrain(rotval1, 0, 100);

  // Print the value to the Serial Monitor
  Serial.print("Encoder Value: ");
  Serial.println(rotval1);

  delay(50);  // Small delay to stabilize reading
}
