#if !defined(GADGET_DATETIME_HPP)
#define GADGET_DATETIME_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Request.hpp"

const char *DateTimeUrl = "http://worldtimeapi.org/api/timezone/America/Monterrey";

class DateTime
{

public:
    String date;
    String time;
    bool isDay;

    DateTime()
    {
        date.reserve(16);
        time.reserve(8);
        isDay = false;
    }

    void updateByJson(const String &json)
    {
        StaticJsonDocument<1024> document;
        deserializeJson(document, json);

        String dt = document["datetime"].as<String>();
        date = dt.substring(0, 10);
        time = dt.substring(11, 16);

        int hour = time.substring(0, 2).toInt();

        if (hour > 8 && hour < 20)
        {
            isDay = true;
        }
        else
        {
            isDay = false;
        }

        if (hour > 12)
        {
            hour -= 12;
            String h = String(hour);
            time = h + time.substring(2) + " PM";
        }
        else
        {
            time += " AM";
        }
    }

    void updateByApi() {
        if(WiFi.status() == WL_CONNECTED)
        {
            String json = httpGETRequest(DateTimeUrl);
            Serial.print("Json content: ");
            Serial.println(json);
            updateByJson(json);
        }
    }

};

#endif // GADGET_DATETIME_HPP
