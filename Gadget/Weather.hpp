#if !defined(GADGET_WEATHER_HPP)
#define GADGET_WEATHER_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Request.hpp"

const char *WeatherUrl = "http://api.openweathermap.org/data/2.5/weather?q=Sabinas,MX&APPID=4b6e7642b0809e91ae7b7b28ec0632eb";

class Weather
{

public:
    String main;
    String description;
    float temperature;

    Weather()
    {
        main.reserve(32);
        description.reserve(64);
        temperature = 0;
    }

    void updateByJson(const String &json)
    {
        StaticJsonDocument<1024> document;
        deserializeJson(document, json);

        main = document["weather"][0]["main"].as<String>();
        description = document["weather"][0]["description"].as<String>();
        temperature = document["main"]["temp"].as<float>();
        temperature -= 273.15;

        main.trim();
        main.toLowerCase();
        description.trim();
        description.toLowerCase();
    }

    void updateByApi() {
        if(WiFi.status() == WL_CONNECTED)
        {
            String json = httpGETRequest(WeatherUrl);
            // Serial.print("Json content: ");
            // Serial.println(json);
            updateByJson(json);
        }
    }

};

#endif // GADGET_WEATHER_HPP
