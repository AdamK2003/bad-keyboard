#include <Arduino.h>
#include <RotaryEncoder.h>
#include "font.h"




// Shift register pins
  int srDataPin    = 4; // SER
  int srLatchPin   = 5; // SRCLK
  int srClockPin   = 6; // RCLK

// Rotary encoder pins
  int rePin1 = 2;
  int rePin2 = 3;

// Button pin, attach button from +5v to this pin, attach this pin to GND through 10K resistor
  int buttonPin = A5;

// Dotmatrix rows, first pin is top row 
  int rows[8] = {7,8,9,10,11,12,A0,A1};
  
// Backspace, return and space characters
  char bksp[8] = { 0x00, 0x00, 0x04, 0x02, 0xFF, 0x00, 0x00, 0x00 };
  char rtrn[8] ={ 0x00, 0x00, 0x40, 0x48, 0x7C, 0x08, 0x00, 0x00 };
  char space[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xFF };




  int prevButtonState = LOW;
  int buttonState = LOW;

  RotaryEncoder encoder(rePin1, rePin2, RotaryEncoder::LatchMode::FOUR3);

  int charNum = 64;

void setup() 
{
  pinMode(srLatchPin,   OUTPUT);
  pinMode(srDataPin,    OUTPUT);  
  pinMode(srClockPin,   OUTPUT);

  pinMode(buttonPin, INPUT);

  for(int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++) {
    digitalWrite(rows[i], HIGH);
  }

  Serial.begin(38400);
}


void loop() 
{

  encoder.tick();
  

  charNum = encoder.getPosition() >= 0 ? ((encoder.getPosition() + 35) % 97 + 30) : (((unsigned(encoder.getPosition()) - 60) % 97 + 34) % 97 + 30);


  if(charNum <= 32) {
    writeBitmap(charNum == 30 ? bksp : charNum == 31 ? rtrn : space);
  } else {
    writeBitmapFont(font, charNum);
  }

  buttonState = digitalRead(buttonPin);

	if (buttonState != prevButtonState) {
    prevButtonState = buttonState;
    if(buttonState == HIGH) {
      Serial.write(charNum);
    }
  }
}

void writeBitmap(char bitmap[8]) {
  for(int i = 0; i < 8; i++) {
    digitalWrite(srLatchPin, LOW);
    shiftOut(srDataPin, srClockPin, MSBFIRST, bitmap[i]);
    digitalWrite(rows[i > 0 ? i-1 : 7], HIGH);
    digitalWrite(srLatchPin, HIGH);
    digitalWrite(rows[i], LOW);
  }
}

void writeBitmapFont(char fontArray[][8], int fontIndex) {
  for(int i = 0; i < 8; i++) {
    digitalWrite(srLatchPin, LOW);
    shiftOut(srDataPin, srClockPin, MSBFIRST, fontArray[fontIndex][i]);
    digitalWrite(rows[i > 0 ? i-1 : 7], HIGH);
    digitalWrite(srLatchPin, HIGH);
    digitalWrite(rows[i], LOW);
  }
}
