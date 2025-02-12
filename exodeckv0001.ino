#include <BleKeyboard.h>
BleKeyboard bleKeyboard("ExoDeck V1", "AndreasBlindheim", 100); //Name, Manufacturer, Battery

//Pins
const int b1 = 2;
const int b2; //= 1;
const int b3; //= 2;
const int b4; //= 3;

const int rotary1; //= 4;
const int rotary2; //= 5;
const int rotary3; //= 6;
const int rotary4; //= 7;



//Variables

int b1val = 0; //Variable that stores current state of button.
int b2val = 0;
int b3val = 0;
int b4val = 0;

unsigned long b1last; //Variable that stores the last time the button was pressed with internal clock.
unsigned long b2last;
unsigned long b3last;
unsigned long b4last;


const int buttonpressdebouce = 50; //The time it should be since last button press in milliseconds




void setup() {
  bleKeyboard.begin(); //Starts the bluetooth keyboard

  //pinmode
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);

  pinMode(rotary1, INPUT);
  pinMode(rotary2, INPUT);
  pinMode(rotary3, INPUT);
  pinMode(rotary4, INPUT);


}

void loop() {
  
  if(bleKeyboard.isConnected()) {

    //Read all componenents
    b1val = digitalRead(b1);
    b2val = digitalRead(b2);
    b3val = digitalRead(b3);
    b4val = digitalRead(b4);

    if(b1val == 1 && millis() - b1last > buttonpressdebouce){ //Condition that check if the button is currectly pressed and that millis() - b1last is more than buttonpressdebounce.
      
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('L');
      delay(50);
      bleKeyboard.releaseAll();
      buttonpressdebouce = millis();
    } 




  }

}
