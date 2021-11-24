/**
 * Created by Juan Jesús Chávez Villa
 */

#ifndef ROSELINO_CLOCK_HPP
#define ROSELINO_CLOCK_HPP

#include "Arduino.h"

#define SECOND (1000)
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)
#define DAY (24 * HOUR)

namespace Rln {

    typedef unsigned long Time;

    class Clock {

    private:
        Time start;

    public:
        Time elapsed() const;

        Clock();

        Time restart();

    };

}

typedef Rln::Clock Clock;

#include "Clock.cpp"

#endif