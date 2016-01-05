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

//  if (digitalRead(a) == LOW) {
//    //    myserial.write('a');
//    Serial.print('a');
//    Serial.write('a');
//  }
  if (digitalRead(b) == LOW) {
    //    myserial.write('b');
    Serial.print('b');
    Serial.write('b'); //b for brakes
  }

  if (digitalRead(c) == LOW) {
    //    myserial.write('c');
    Serial.print('c');
    Serial.write('z'); // z for z trigger

  }


  if (digitalRead(d) == LOW) {
    //    myserial.write('d');
    Serial.print('d');
    Serial.write('d');
  }

  if (digitalRead(e) == LOW) {
    //    myserial.write('e');
    Serial.print('e');
    Serial.write('s'); //s for start

  }

  if (digitalRead(f) == LOW) {
    //    myserial.write('f');
    Serial.print('f');
    
    Serial.write('f');

  }

  if (digitalRead(g) == LOW) {
    //    myserial.write('g');
    Serial.print('g');
    Serial.write('g');
  }


  if (digitalRead(h) == LOW) {
    //    myserial.write('h');
    Serial.print('h');
    Serial.write('h');

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
  Serial.println();
  delay(150);

}

