#include "Arduino.h"
#include "Roselino/Digital.hpp"

Digital input(2, INPUT);
Digital out_state(3, OUTPUT);
Digital out_rising(4, OUTPUT);
Digital out_falling(5, OUTPUT);

bool rising_state = false;
bool falling_state = false;

void setup()
{
    /* Do nothing */
}

void loop()
{
    out_state.write(input.read());
    if (input.rising())
    {
        out_rising.write(rising_state = !rising_state);
    }
    if (input.falling())
    {
        out_falling.write(falling_state = !falling_state);
    }
}