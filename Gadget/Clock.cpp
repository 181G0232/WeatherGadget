/**
 * Created by Juan Jesús Chávez Villa
 */

#ifndef ROSELINO_CLOCK_CPP
#define ROSELINO_CLOCK_CPP

#include "Arduino.h"
#include "Clock.hpp"

namespace Rln {

    Time Clock::elapsed() const {
        return millis() - start;
    }

    Clock::Clock() : start(millis()) {}

    Time Clock::restart() {
        auto current = millis();
        auto interval = current - start;
        start = current;
        return interval;
    }

}

#endif // GUARD ROSELINO_CLOCK_CPP