#if !defined(GADGET_OLED_HPP)
#define GADGET_OLED_HPP

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Oled
{

public:
    Adafruit_SSD1306 display;

    Oled() : display(128, 64, &Wire, -1) {}

    bool init()
    {
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        {
            return false;
        }
        display.cp437(true);
        display.setTextColor(WHITE);
        return true;
    }

    void clear()
    {
        display.clearDisplay();
        display.display();
    }

    void drawBackground()
    {
        display.drawRect(0, 0, 128, 64, WHITE);
        display.display();
    }

    void drawIcon(const uint8_t *icon)
    {
        display.drawBitmap(92, 28, icon, 32, 32, 1);
        display.display();
    }

    void drawTemperature(float temperature)
    {
        display.setTextSize(2);
        display.setCursor(4, 28);
        display.print(temperature);
        display.write(248);
        display.println("C");
        display.display();
    }

    void drawMainWeather(const String &main)
    {
        display.setTextSize(1);
        display.setCursor(4, 44);
        display.println(main);
        display.display();
    }

    void drawWeatherDescription(const String &description)
    {
        display.setTextSize(1);
        display.setCursor(4, 53);
        display.print(description);
        display.display();
    }

    void drawDate(const String &date)
    {
        display.setTextSize(1);
        display.setCursor(64, 4);
        display.println(date);
        display.display();
    }

    void drawTime(const String &time)
    {
        display.setTextSize(1);
        display.setCursor(4, 4);
        display.println(time);
        display.display();
    }
};

#endif // GADGET_OLED_HPP
