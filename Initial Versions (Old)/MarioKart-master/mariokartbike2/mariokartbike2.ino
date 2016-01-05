#include <SoftwareSerial.h> //Needed to communicate with other arduino for multiplexing / more IO

#include <Keyboard.h> //Only works with Ardunios based on ATMega 32u4 (leonardo, micro, ect)


/* This is the code to run handlebar turning and wheel speed sensing for Mario Kart integration. Revision 2.2.*/

/*
  PIN 13 =
  PIN 12 =
  PIN 11 = Enable/Disable
  PIN 10 =
  PIN 9 = SERIAL RX ##CONNECT TO PIN 0 OF UNO
  PIN 8 = SERIAL TX ##CONNECT TO PIN 1 OF UNO
  PIN 7 =
  PIN 6 =
  PIN 5 =button?
  PIN 4 =button?
  PIN 3 =button?
  PIN 2 =button?
  PIN 1 =button?
  PIN 0 = button?
  PIN A0 = WHEEL
  PIN A1 = HANDLEBAR
  PIN A2 =
  PIN A3 =
  PIN A4 =
  PIN A5 =
*/



//second arduino, which must have its own code loaded onto it from MarioKartExtraIO file
SoftwareSerial myserial(9, 8); // rx, tx


//system control variables
boolean keyboardEnabled = false; //Need ability to turn keyboard on and off, state of keyboard activation held here.
int previousButtonState = HIGH; //previous state of keyboard enable button //MIGHT NOT WANT TO USE THIS ONE
int buttonState; //current state of enable button
int e = 0; //used to keep track of how many times the button has been pressed, toggles enable/disable.
const int keyboardEnableButton = 11; //Pin that physical switch to enable keyboard is on;
const int keyboardEnableLED = 13; //LED indicator for visual indication of enabled-ness.

//sensor location variables
const int handlebarSensor = A1; //Pin that handlebar rotational sensor is on.
const int hallSensor = A0; //Pin that the Hall Effect sensor in the wheel is on.


//sensor data variables
int handlebar = 0; //value of handlebar rotation
int wheel = 0; //value from wheel sensor
int buttonPressed; // stores button values from second arduino as integers representing ASCII
String str;
char keyToBePressed; // converted ASCII value from buttonPressed
boolean keyIsYetToBePressed = false; //Used to stop infinite key presses in button input from other arduino.


//control mapping variables
const char accelerate = 'a'; //keyboard button to accelerate in Mario Kart
const char turnLeft = 'l'; //keyboard button to turn left in Mario Kart
const char turnRight = 'r';// keyboard button to turn right in Mario Kart


void setup() {
  Serial.begin(9600); //always a good idea to have the serial going for debugging.
  myserial.begin(9600); //used for more IO
  pinMode(keyboardEnableButton, INPUT); //Set enable button as input
  pinMode(keyboardEnableLED, OUTPUT); //LED indicator
  //previousButtonState = digitalRead(keyboardEnableButton); //initialize the system for detecting if the button has changed
  previousButtonState = LOW;


}


void loop() {

  buttonState = digitalRead(keyboardEnableButton); //make sure we haven't pressed the enable/disable button


  if (buttonState != previousButtonState) { //toggle the enable/disable button on or off
    previousButtonState = buttonState;
    Serial.println("Button Changed");
    Serial.println(buttonState);
    if (buttonState == HIGH) {
      toggleKeyboard();
    }
  }

  if (myserial.available()) { //takes in chars on the software serial line and turns them into keyboard presses
    serialRecieveAndProcess(); //handle software serial input data and press appropriate keyboard keys.
  }

  if (keyboardEnabled) {
    digitalWrite(keyboardEnableLED, HIGH); //send a visual signal that the system is armed
    tightLoop(); //runs the rest of the code here, so that other things in regular loop() can be skipped if they're not needed.
  }
  else {
    digitalWrite(keyboardEnableLED, LOW); //default the system arm light to off
  }



}

void tightLoop() {
 // Serial.println("fuckign tightloop ran");
 debugData();
 Keyboard.begin(); //begin keyboard emulation
//Serial.print("keyboard bagan");
  wheel = digitalRead(hallSensor); //get actual data
  handlebar = analogRead(handlebarSensor);

  if (handlebar > 850) { //handlebar turns right, turn kart right
    Keyboard.release(turnLeft);
    Keyboard.press(turnRight); //press the key
  Serial.print("the wheel is right");
//    if (handlebar > 925) { //if the handlebar is even farther right
//      Keyboard.write(turnRight); //press the key again
    
  }

  else if (handlebar < 730) { //handlebar turns left, turn left
    Keyboard.release(turnRight);
    Keyboard.press(turnLeft);   //press the key
    Serial.print("the wheel is left");
//    
//    if (handlebar < 700) { //if the handlebar is even farther left
//      Keyboard.write(turnLeft); //press the key again
    
  }
   if(handlebar <850 && handlebar >730){
    Serial.print("the wheel is in the middle");
    Keyboard.releaseAll();
    }
  
wheel = digitalRead(hallSensor); //get actual data
  if (wheel == HIGH) { //acceleration segment
    Keyboard.press(accelerate); //press the key
    Serial.print("hit accel");
   delay(50);
  }
    Keyboard.release(accelerate);

// serialRecieveAndProcess(); //handle software serial input data and press appropriate keyboard keys.
 Keyboard.end(); //end keyboard emulation

debugData();
}

void serialRecieveAndProcess() {

  keyIsYetToBePressed = true;
  buttonPressed = myserial.read();
//  str = str.(buttonPressed);
Serial.print("the button pressed reads: ");
Serial.print(buttonPressed);
  keyToBePressed = char(buttonPressed);
  Serial.println("key to be pressed");
   Serial.print(keyToBePressed);
delay(200);
  if (keyboardEnabled && keyIsYetToBePressed == true) {
    Keyboard.write(keyToBePressed); //output the button press as a keyboard command
    keyIsYetToBePressed = false;
  }
 // debugData();
}


void toggleKeyboard() {
  e++;
  e = e % 2;
  Serial.print("e is: ");
  Serial.println(e);
  if (e == 1) { //if e is 1
    Serial.println("Keyboard Enabled");
    //    Keyboard.begin(); //begin keyboard emulation
    keyboardEnabled = true;
  }
  if (e == 0) { //if e is 0 do the opposite.
    Serial.println("Keyboard Disabled");
    //    Keyboard.end(); //end keyboard emulation
    keyboardEnabled = false;
  }
}

void debugData() {

  wheel = digitalRead(hallSensor); //get actual data
  handlebar = analogRead(handlebarSensor);

  Serial.print("handlebar: ");
  Serial.println(handlebar);

  Serial.print("wheel: ");
  Serial.println(wheel);

}
