#ifndef ROSELINO_DIGITAL_CPP
#define ROSELINO_DIGITAL_CPP

#include "Arduino.h"
#include "Digital.hpp"

namespace ro
{

    void Digital::setup()
    {
        pinMode(pin, mode);
    }

    bool Digital::read() const
    {
        if (mode == INPUT)
        {
            bool value = digitalRead(pin);
            m_rising = !m_value && value;
            m_falling = m_value && !value;
            m_value = value;
        }
        return m_value;
    }

    void Digital::write(bool value)
    {
        m_value = value;
        m_rising = !m_value && value;
        m_falling = m_value && !value;
        if (mode == OUTPUT)
        {
            digitalWrite(pin, m_value);
        }
    }

    void Digital::set()
    {
        write(HIGH);
    }

    void Digital::reset()
    {
        write(LOW);
    }

    bool Digital::isHigh() const
    {
        return read();
    }

    bool Digital::isLow() const
    {
        return !read();
    }

    bool Digital::rising() const {
        return m_rising;
    }

    bool Digital::falling() const {
        return m_falling;
    }

    Digital::Digital(uint8_t _pin, uint8_t _mode)
        : pin(_pin),
          mode(_mode),
          m_value(false)
    {
        setup();
    }

}

#endif // GUARD ROSELINO_DIGITAL_CPP