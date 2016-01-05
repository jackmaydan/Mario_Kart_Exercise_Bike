//basically the potentiometer is messed up. it won't read anything to the left of "front". So we rotate the board and use the working 180 degrees on the right side of "front". Use this to calibrate the potent which is affected by magnetic fields appartently.

int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
}

void loop() {
  val = analogRead(A1);    // read the value from the sensor
  Serial.println(val);               // stop the program for some time
}
