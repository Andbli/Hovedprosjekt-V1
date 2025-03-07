/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-library
 *
 * This example:
 *   + uses debounce for multiple buttons.
 *   + reads state of multiple buttons
 *   + detects the pressed and released events of multiple buttons
 */

#include <ezButton.h>

ezButton button1(32);  // create ezButton object that attach to pin 6;
ezButton button2(33);  // create ezButton object that attach to pin 7;
ezButton button3(25);  // create ezButton object that attach to pin 8;
ezButton button4(26);  // create ezButton object that attach to pin 8;

void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds
  button4.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first
  button4.loop(); // MUST call the loop() function first

  //  int btn1State = button1.getState();
  //  int btn2State = button2.getState();
  //  int btn3State = button3.getState();


  if(button1.isPressed())
    Serial.println("The button 1 is pressed");

  if(button1.isReleased())
    Serial.println("The button 1 is released");

  if(button2.isPressed())
    Serial.println("The button 2 is pressed");

  if(button2.isReleased())
    Serial.println("The button 2 is released");

  if(button3.isPressed())
    Serial.println("The button 3 is pressed");

  if(button3.isReleased())
    Serial.println("The button 3 is released");

    if(button4.isPressed())
    Serial.println("The button 4 is pressed");

  if(button4.isReleased())
    Serial.println("The button 4 is released");

}
