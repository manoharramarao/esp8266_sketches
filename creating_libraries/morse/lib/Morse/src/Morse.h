/*
  Morse.h - Library for flashing Morse code.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
    public:
        Morse(int pin);
        void dot();
        void dash();
    private:
        int _pin;
};

#endif
