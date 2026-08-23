#include <Arduino.h>

const int ledPin = LED_BUILTIN;  // pin 13 on Teensy 4.1

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
}