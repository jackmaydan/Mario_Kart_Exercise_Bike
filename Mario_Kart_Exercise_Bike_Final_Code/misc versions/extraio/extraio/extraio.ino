#include <SoftwareSerial.h>

//this is the code for the second arduino in the MarioKart project.
//This can be any arduino, and it's only purpose is for extra buttons
//without needing a single processor to watch them all.
//test

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
  PIN 0 = SWERIAL RX
  ###CERTAIN PINS DO NOT WORK, DUE TO WIRING ERRORS. SECTIONS OF THE CODE RELATING TO THOSE PINS HAS BEEN COMMENTED OUT###

*/
//SoftwareSerial myserial(9, 8); // rx, tx

//button variables go here

const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int h = 9;
//const int i = 10;
//const int j = 11;
//const int k = 12;

void setup() {

  //  myserial.begin(9600); //open serial line
  Serial.begin(9600);

  for (int i = 2; i <= 12; i++) //buttons 0 through 7 are used for input from handlebar buttons;
  {
    pinMode(i, INPUT);
  }
}

void loop() {

  if (digitalRead(a) == LOW) {
    //    myserial.write('a');
    Serial.write('a');
    delay(50);
  }
  if (digitalRead(b) == LOW) {
    //    myserial.write('b');
    Serial.write('b');
    delay(50);
  }

  if (digitalRead(c) == LOW) {
    //    myserial.write('c');
    Serial.write('c');
    delay(50);
  }

  if (digitalRead(d) == LOW) {
    //    myserial.write('d');
    Serial.write('d');
    delay(50);
  }

  if (digitalRead(e) == LOW) {
    //    myserial.write('e');
    Serial.write('e');
    delay(50);
  }

//  if (digitalRead(f) == LOW) {
//    //    myserial.write('f');
//    Serial.write('f');
//    delay(50);
//  }

  if (digitalRead(g) == LOW) {
    //    myserial.write('g');
    Serial.write('g');
    delay(50);
  }

  if (digitalRead(h) == LOW) {
    //    myserial.write('h');
    Serial.write('h');
    delay(50);
  }

  //  if (digitalRead(i) == LOW) {
  //    //    myserial.write('i');
  //    Serial.write('i');
  //
  //  }
  //  if (digitalRead(j) == LOW) {
  //    //    myserial.write('j');
  //    Serial.write('j');
  //
  //  }
  //  if (digitalRead(k) == LOW) {
  //    //    myserial.write('k');
  //    Serial.write('k');
  //  }

//  Serial.write("running");

}

