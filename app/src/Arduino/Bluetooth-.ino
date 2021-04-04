/** https://42bots.com/tutorials/hc-06-bluetooth-module-datasheet-and-configuration-with-arduino/ **/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10); // RX, TX

String command = ""; // Stores response of the HC-06 Bluetooth device

//TODO :: LED
const int pinled = 13;
const int redLED = 3;
const int greenLED = 4;
const int blueLED = 5;

const int myDelay = 1000;

void setup() {
  // Open serial communications:
  Serial.begin(9600);
  Serial.println("Type AT commands!");

  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);

  // init LED
  pinMode(pinled, OUTPUT);
  digitalWrite(pinled, LOW);
  pinMode(redLED, OUTPUT);
  digitalWrite(redLED, LOW);
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  pinMode(blueLED, OUTPUT);
  digitalWrite(blueLED, LOW);
  setColourRgb(0,0,0);

}

void loop() {
  // Read device output if available.
  if (mySerial.available()) {
    while (mySerial.available()) { // While there is more to be read, keep reading.
      command += (char)mySerial.read();
    }

    Serial.println(command);

    //TODO :: toggle LED based on inputs: 0 1
    switch (command[0]) {
      case '0':
        digitalWrite(pinled, LOW);
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(blueLED, LOW);
        setColourRgb(LOW,LOW,LOW);

        break;

      case '1':
        digitalWrite(pinled, HIGH);
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
        digitalWrite(blueLED, LOW);
        break;
      case '2':
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
        digitalWrite(blueLED, LOW);
        break;
      case '3':
        digitalWrite(blueLED, HIGH);
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);
        break;
      case '4':
        colorChange();
        break;

    }
    command = ""; // No repeats
  }

  // Read user input if available.
  if (Serial.available()) {
    delay(10); // The delay is necessary to get this working!
    mySerial.write(Serial.read());
  }
}

void colorChange() {
  unsigned int rgbColour[3];

  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;  

  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(5);

}
  }
}


void setColourRgb(int red, int green, int blue)
{
  analogWrite(redLED, red);
  analogWrite(greenLED, green);
  analogWrite(blueLED, blue);
}
