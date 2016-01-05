#include <SoftwareSerial.h>

#include <Keyboard.h>



int input;
char output;

SoftwareSerial myserial(8, 9); // rx, tx

void setup() {
  myserial.begin(9600);
}

void loop() {
  if (myserial.available()) {
//    Serial.println("available");
    input = myserial.read();
    output = char(input);
    Keyboard.begin();
    Keyboard.write(output);
    Keyboard.end();
  }
}
