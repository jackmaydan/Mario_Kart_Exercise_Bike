#include <SoftwareSerial.h>

//this is the code for the second arduino in the MarioKart project.
//This can be any arduino, and it's only purpose is for extra buttons
//without needing a single processor to watch them all.
//test
//##ideas to stop spam##
// put a 10ms delay in each loop, will only freeze the unrrrrrrrro board not the entire process
//

/*
  PIN 13 = UNOCCPIED
  PIN 12 = IO
  PIN 11 = IO
  PIN 10 = IO
  PIN 9 = IO
  PIN 8 = io
  PIN 7 = IO
  PIN 6 = IO
  PIN 5 = IO
  PIN 4 = IO
  PIN 3 = IO
  PIN 2 = IO
  PIN 1 = SERIAL TX
  PIN 0 = SERIAL RX
*/
//SoftwareSerial myserial(9, 8); // rx, tx

//button variables go here

const int x = 2;
//const int b = 3;//unused yellow wire that's cut
const int c = 4;
const int d = 5; 
const int e = 6;
//const int f = 7; // empty pin nothing plugged in
const int g = 8;
const int h = 9;
const int i = 10;
const int j = 11;
const int k = 12;

void setup() {

  
  Serial.begin(9600);

  for (int i = 2; i <= 12; i++) 
  {
    pinMode(i, INPUT);
  }
}

void loop() {

//B Button (brake)
  if (digitalRead(x) == LOW) {
 //   delay(50);
    Serial.write('b');
  }
  
//  if (digitalRead(b) == LOW) {
//    //    myserial.write('b');
//    Serial.write('b');
//  }

//left bumper (volume?)
  if (digitalRead(c) == LOW) {

    Serial.write('p');

  }
//Start Button (red start button)
 if (digitalRead(d) == LOW) {
  
  Serial.write('s');
  }
//Z Button (activate powerup)
  if (digitalRead(e) == LOW) {
    
    Serial.write('e');

  }

 // if (digitalRead(f) == LOW) {

 //  Serial.write('f');

 //}
 
//C Down (yellow down arrow)
  if (digitalRead(g) == LOW) {
    
    Serial.write('g');
  }
//C Left (yellow left arrow
  if (digitalRead(h) == LOW) {

    Serial.write('h');

  }
//C Up (yellow up arrow)
  if (digitalRead(i) == LOW) {
   
   Serial.write('i');

  }
  //C Right (yellow right arrow)
 if (digitalRead(j) == LOW) {

    Serial.write('f');

 }

 //Right Bumper (right grey trigger)
  if (digitalRead(k) == LOW) {
    //    myserial.write('k');
   Serial.write('k');
  }
  
  delay(123);

}
