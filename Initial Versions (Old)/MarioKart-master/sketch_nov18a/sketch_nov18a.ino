#include <SoftwareSerial.h> //Needed to communicate with other arduino for multiplexing / more IO

#include <Keyboard.h> //Only works with Ardunios based on ATMega 32u4 (leonardo, micro, ect)


/* This is the code to run handlebar turning and wheel speed sensing for Mario Kart integration. Revision 2.1. Keyboard.begin and Keyboard.end now in the toggle function, so keyboard emulation doesn't stop and start continiuously.
  Revision 2.0. Major changes to code structure and flow. everything in loop() now broken into separate functions.
  Revision 0.6. "Wheel" is now digital, only on or off.
  Revision 0.5.4. Minor tweaks.
  Revision 0.5.3. Control laws changed.
  Revision 0.5.2. Keyboard.press changed to Keyboard.write, which seems to accomplish the same thing with fewer commands.
  Reivsion 0.5.1. Keyboard.press changed back, with addition of Keyboard.release to let go of the key. Derp.
  Revision 0.5. Keyboard.press changed to Keyboard.print, no "sticky keys."
  Revision 0.4. Now compiles!
  True/False statements fixed and placeholders added to environmental varaibles since 0.3.
  Enable button flow code improved since 0.2.
  Enable button code changed since 0.1.
  Author - Jacob Killelea, team Breakfast Summit, COEN 1400, CU Boulder, Fall 2015.
  This code is licensed under the GNU GPL V3 and hopes to be useful, but there is no warranty or guarantee of usefulness, implied or otherwise.
*/

/*
  PIN 13 =
  PIN 12 =
  PIN 11 = Enable/Disable
  PIN 10 =
  PIN 9 = SERIAL TX ##CONNECT TO PIN 0 OF UNO
  PIN 8 = SERIAL RX ##CONNECT TO PIN 1 OF UNO
  PIN 7 =
  PIN 6 =
  PIN 5 =
  PIN 4 =
  PIN 3 =
  PIN 2 =
  PIN 1 =
  PIN 0 =
  PIN A0 = HANDLEBARR
  PIN A1 = WHEEL
  PIN A2 =
  PIN A3 =
  PIN A4 =
  PIN A5 =
*/



//second arduino, which must have its own code loaded onto it from MarioKartExtraIO file
SoftwareSerial myserial(8, 9); // rx, tx


//system control variables
boolean keyboardEnabled = false; //Need ability to turn keyboard on and off, state of keyboard activation held here.
int previousButtonState = HIGH; //previous state of keyboard enable button //MIGHT NOT WANT TO USE THIS ONE
int buttonState; //current state of enable button
int e = 0; //used to keep track of how many times the button has been pressed, toggles enable/disable.
const int keyboardEnableButton = 11; //Pin that physical switch to enable keyboard is on;
const int keyboardEnableLED = 13; //LED indicator for visual indication of enabled-ness.

//sensor location variables
const int handlebarSensor = A0; //Pin that handlebar rotational sensor is on.
const int hallSensor = A1; //Pin that the Hall Effect sensor in the wheel is on.


//sensor data variables
int handlebar = 0; //value of handlebar rotation
int wheel = 0; //value from wheel sensor
int buttonPressed; // stores button values from second arduino as integers representing ASCII
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
  debugData();
}

void tightLoop() {

  Keyboard.begin(); //begin keyboard emulation

  wheel = digitalRead(hallSensor); //get actual data
  handlebar = analogRead(handlebarSensor);

  if (handlebar > 600) { //handlebar turns right, turn kart right
    Keyboard.write(turnRight); //press the key
    if (handlebar > 800) { //if the handlebar is even farther right
      Keyboard.write(turnRight); //press the key again
    }
  }

  else if (handlebar < 400) { //handlebar turns left, turn left
    Keyboard.write(turnLeft);   //press the key
    if (handlebar < 200) { //if the handlebar is even farther left
      Keyboard.write(turnLeft); //press the key again
    }
  }

  if (wheel == HIGH) { //acceleration segment
    Keyboard.write(accelerate); //press the key
    Keyboard.write(accelerate); //press it again so we go faster. FASTER! FAAAAAAAAAAAAAAAAAAASTER!
  }

  Keyboard.end(); //end keyboard emulation


}

void serialRecieveAndProcess() {

  keyIsYetToBePressed = true;
  buttonPressed = myserial.read();
  keyToBePressed = char(buttonPressed);
  Serial.println(keyToBePressed);

  if (keyboardEnabled && keyIsYetToBePressed == true) {
    Keyboard.write(keyToBePressed); //output the button press as a keyboard command
    keyIsYetToBePressed = false;
  }
}


void toggleKeyboard() {
  e++;
  e = e % 2;
  Serial.print("e is: ");
  Serial.println(e);
  if (e == 1) { //if e is 1
    Serial.println("Keyboard Enabled");
    Keyboard.begin(); //begin keyboard emulation
    keyboardEnabled = true;
  }
  if (e == 0) { //if e is 0 do the opposite.
    Serial.println("Keyboard Disabled");
    Keyboard.end(); //end keyboard emulation
    keyboardEnabled = false;
  }
}

void debugData() {
  
  Serial.print("handlebar:");
  Serial.println(analogRead(handlebarSensor));

  Serial.print("wheel");
  Serial.println(digitalRead(hallSensor));
  //    Serial.print("");
  //  Serial.println();
  //    Serial.print("");
  //  Serial.println();

}
