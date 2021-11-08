#ifndef ROSELINO_DIGITAL_HPP
#define ROSELINO_DIGITAL_HPP

namespace ro
{

    class Digital
    {

    private:
        mutable bool m_value;
        mutable bool m_rising;
        mutable bool m_falling;

    public:
        const uint8_t pin;
        const uint8_t mode;

        void setup();

        bool read() const;
        void write(bool signal);

        void set();
        void reset();

        bool isHigh() const;
        bool isLow() const;

        bool rising() const;
        bool falling() const;

        Digital(uint8_t _pin, uint8_t _mode);
    };

}

#include "Digital.cpp"

typedef ro::Digital Digital;

#endif // GUARD ROSELINO_DIGITAL_HPP