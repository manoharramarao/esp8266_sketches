/*
  Morse.cpp - Library for flashing Morse code.
*/

#include "Morse.h"

Morse morse(LED_BUILTIN);

void setup() {

}

void loop() {
  morse.dot();morse.dot();morse.dot();
  morse.dash();morse.dash();morse.dash();
  morse.dot();morse.dot();morse.dot();
  delay(3000);
}
