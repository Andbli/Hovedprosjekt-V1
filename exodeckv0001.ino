#include <BleKeyboard.h>
BleKeyboard bleKeyboard("ExoDeck V1", "AndreasBlindheim", 100); //Name, Manufacturer, Battery

//Pins
const int b1 = 18;
const int b2 = 19;
const int b3 = 20;
const int b4 = 21;

//const int rotary1 = 4;
//const int rotary2 = 5;
//const int rotary3 = 6;
//const int rotary4 = 7;



//Variables

int b1val = 0; //Variable that stores current state of button.
int b2val = 0;
int b3val = 0;
int b4val = 0;

unsigned long b1last = millis(); //Variable that stores the last time the button was pressed with internal clock. Set this variable to millis at boot so they have a value, alternativly 0.
unsigned long b2last = millis();
unsigned long b3last = millis();
unsigned long b4last = millis();


const int buttonpressdebouce = 50; //The time it should be since last button press in milliseconds




void setup() {
  bleKeyboard.begin(); //Starts the bluetooth keyboard
  delay(500); //Delay for stability!

  //pinmodes
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);

//  pinMode(rotary1, INPUT);
//  pinMode(rotary2, INPUT);
//  pinMode(rotary3, INPUT);
//  pinMode(rotary4, INPUT);


}

void loop() {
  
  if(bleKeyboard.isConnected()) {

    //Read all componenents
    b1val = digitalRead(b1);
    b2val = digitalRead(b2);
    b3val = digitalRead(b3);
    b4val = digitalRead(b4);

    if(b1val == LOW && millis() - b1last > buttonpressdebouce){ //Condition that check if the button is currectly pressed and that millis() - b1last is more than buttonpressdebounce.
      
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('l');
      delay(50);
      bleKeyboard.releaseAll();
      b1last = millis();
    } 

    if(b2val == LOW && millis() - b2last > buttonpressdebouce){ //Condition that check if the button is currectly pressed and that millis() - b1last is more than buttonpressdebounce.
      
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('l');
      delay(50);
      bleKeyboard.releaseAll();
      b2last = millis();
    } 

    if(b3val == LOW && millis() - b3last > buttonpressdebouce){ //Condition that check if the button is currectly pressed and that millis() - b1last is more than buttonpressdebounce.
      
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('l');
      delay(50);
      bleKeyboard.releaseAll();
      b3last = millis();
    } 

    if(b4val == LOW && millis() - b4last > buttonpressdebouce){ //Condition that check if the button is currectly pressed and that millis() - b1last is more than buttonpressdebounce.
      
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('l');
      delay(50);
      bleKeyboard.releaseAll();
      b4last = millis();
    } 




  }

}
