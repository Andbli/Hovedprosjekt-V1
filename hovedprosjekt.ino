//Libraries
#include <Wire.h> //Onewire for screen
#include <Adafruit_GFX.h> //Graphics library for screen
#include <Adafruit_SSD1306.h> //Screen library
#include <AiEsp32RotaryEncoder.h> //Library for easy rotary encoder management
#include <ezButton.h> //Library for easy button management
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Exodeck", "AndreasBlindheim", 100); //Device Name, Device Manufacturer, Battery Percentage



// --- Screen Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ezButton button1(13);  // creates ezButton object
ezButton button2(14);  // create ezButton object
ezButton button3(27);  // create ezButton object
ezButton button4(26);  // create ezButton object
ezButton brot1(16); //Create a ezButton object for rotary encoder 1.
ezButton brot2(18); //Create a ezButton object for rotary encoder 2.


int privval1 = 0; //Privval1 og value1 blir brukt til å styre rotary encoder mekansimen, slik vi kan sende en kommando når den snurrar en veg og en den andre vegen.
int privval2 = 0; //Privval2 og value2 blir brukt til å styre rotary encoder mekansimen, slik vi kan sende en kommando når den snurrar en veg og en den andre vegen.

// --- Rotary Encoders Pin Definitions ---
#define ENCODER1_A 4
#define ENCODER1_B 23
#define ENCODER2_A 17
#define ENCODER2_B 5


// --- Rotary Encoder Value Range ---
#define MIN_VALUE 0
#define MAX_VALUE 100

// --- Create Rotary Encoder Objects ---
AiEsp32RotaryEncoder encoder1(ENCODER1_A, ENCODER1_B, -1, -1, 4);
AiEsp32RotaryEncoder encoder2(ENCODER2_A, ENCODER2_B, -1, -1, 4);


// --- Interrupt Service Routines ---
void IRAM_ATTR handleEncoder1() { encoder1.readEncoder_ISR(); }
void IRAM_ATTR handleEncoder2() { encoder2.readEncoder_ISR(); }


void setup() {
  Serial.begin(9600);
  bleKeyboard.begin();

//Button DebouceTime
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds
  button4.setDebounceTime(50); // set debounce time to 50 milliseconds
  brot1.setDebounceTime(50); // set debounce time to 50 milliseconds
  brot2.setDebounceTime(50); // set debounce time to 50 milliseconds


  // PinModes
  pinMode(ENCODER1_A, INPUT_PULLUP);
  pinMode(ENCODER1_B, INPUT_PULLUP);
  pinMode(ENCODER2_A, INPUT_PULLUP);
  pinMode(ENCODER2_B, INPUT_PULLUP);


  // Begin and configure the encoders
  encoder1.begin();
  encoder2.begin();
  encoder1.setup(handleEncoder1);
  encoder2.setup(handleEncoder2);

  //Sets start value
  encoder2.setEncoderValue(50);

  // Set boundaries and acceleration for each encoder
  encoder1.setBoundaries(-900000, 900000, true);
  encoder2.setBoundaries(-900000, 900000, true);
  encoder1.setAcceleration(20);
  encoder2.setAcceleration(0);


  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
}

void loop() {
  // Read current values from all three encoders
  int value1 = encoder1.readEncoder();
  int value2 = encoder2.readEncoder();

  button1.loop(); // Start Read the button
  button2.loop(); 
  button3.loop(); 
  button4.loop(); 
  brot1.loop();
  brot2.loop();




//------------------------------------------Display Logic-----------------------------------------------------
  // Clear display before drawing new content
  display.clearDisplay();

  // Define vertical offsets for each encoder section
  int offset1 = 0;   // Section 1: rows 0 - 20
  int offset2 = 21;  // Section 2: rows 21 - 41

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


  // Refresh the display
  display.display();



//------------------------------------------Rotary Encoder 1-----------------------------------------------------
  if(value1 > privval1){
    Serial.print("Vol+");
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    privval1 = value1;
  }

  if(value1 < privval1){
    Serial.print("Vol-");
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    privval1 = value1;
  }

  if(brot1.isPressed()){
    //Serial.println("Rotary Encoder 1 pressed!");
    bleKeyboard.write(KEY_MEDIA_MUTE);

  }

  if(brot1.isReleased()){
    //Serial.println("Rotary Encoder 1 released!");

  }


//------------------------------------------Rotary Encoder 2-----------------------------------------------------
   if(value2 > privval2){
    //Serial.print("Volume +");
    bleKeyboard.write(KEY_RIGHT_ARROW);
    privval2 = value2;
  }

  if(value2 < privval2){
    //Serial.print("Volume Down");
    bleKeyboard.write(KEY_LEFT_ARROW);
    privval2 = value2;
  }
 
  if(brot2.isPressed()){
    //Serial.println("Mute!");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

  }

  if(brot2.isReleased()){
    //Serial.println("Rotary Encoder 2 released!");

  }
 


//------------------------------------------Button 1-----------------------------------------------------
 
  if(button1.isPressed()){
    Serial.println("B1 Pressed");
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press('l');
  }

  if(button1.isReleased()){
    Serial.println("B1 Released");
    delay(100);
    bleKeyboard.releaseAll();
  }

//------------------------------------------Button 2-----------------------------------------------------

  if(button2.isPressed()){
    Serial.println("B2 Pressed");
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  }

  if(button2.isReleased()){
    Serial.println("B2 Released");
  }

//------------------------------------------Button 3-----------------------------------------------------

  if(button3.isPressed()){
    Serial.println("B3 Pressed");
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
  }

  if(button3.isReleased()){
    Serial.println("B3 Released");
  }

//------------------------------------------Button 4-----------------------------------------------------

  if(button4.isPressed()){
    Serial.println("B4 Pressed");
  }

  if(button4.isReleased()){
    Serial.println("B4 Released");
  }

}
