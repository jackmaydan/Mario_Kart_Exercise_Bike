
//JACK MAYDAN CODE VERSION X FOR MARIO KART BIKE
//Jake Killelea has no contribution to this code
//Code is not open source and restricted only to me under the FU license v 3.420
int buttonState = 0;


#include <SoftwareSerial.h>
void setup() {
  Serial.begin(9600);
  SoftwareSerial myserial(8, 9);

 pinMode(0,INPUT);
  pinMode(1,INPUT);
   pinMode(2,INPUT);
    pinMode(3,INPUT);
     pinMode(4,INPUT);
      pinMode(5,INPUT);
       pinMode(6,INPUT);
        pinMode(13, OUTPUT);
}

void loop() {

   // read the state of the pushbutton value:
  buttonState = digitalRead(4);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(13, HIGH);
  } else {
    // turn LED off:
    digitalWrite(13, LOW);
  }
}
