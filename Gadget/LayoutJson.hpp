#ifndef GADGET_LAYOUTJSON
#define GADGET_LAYOUTJSON

#include <Arduino.h>
#include <ArduinoJson.h>

/**
 * This class store the weather display data 
 */
class Weather {

public:
    float temp;
    float tempMin;
    float tempMax;
    float humidity;
    float pressure;
    float windSpeed;
    String description;
    String state;

    int conversionActual;
    int conversionMin;
    int conversionMax;

    Weather() = default;

    Weather(const String& jsonText) {
        StaticJsonDocument<1024> document;
        deserializeJson(document, jsonText);

        state = document["weather"][0]["main"].as<String>();
        description = document["weather"][0]["description"].as<String>();
        temp = document["main"]["temp"].as<float>();
        tempMin = document["main"]["temp_min"].as<float>();
        tempMax = document["main"]["temp_max"].as<float>();
        pressure = document["main"]["pressure"].as<float>();
        humidity = document["main"]["humidity"].as<float>();
        windSpeed = document["wind"]["speed"].as<float>();

        conversionActual = (int)temp - 273.15;

        conversionMin = (int)tempMin - 273.15;
        conversionMax = (int)tempMax - 273.15;

        //state.toLowerCase();
        //description.toLowerCase();
        
        state.trim();
        description.trim();
    }

};

/**
 * This class store the datetime display data
 */
class DateTime
{

public:
    String date;
    String time;
    bool esDia;

    DateTime() = default;

    DateTime(const String& jsonText) {
        StaticJsonDocument<1024> document;
        deserializeJson(document, jsonText);

        String dt = document["datetime"].as<String>();
        date = dt.substring(0, 10);
        time = dt.substring(11, 16);

        int hour = time.substring(0, 2).toInt();

        if(hour > 8 && hour < 20) {
            esDia = true;
        } else {
            esDia = false;
        }

        if(hour > 12) {
            hour -= 12;
            String h = String(hour);
            time = h + time.substring(2) + " PM";
        }
        else
        {
            time += " AM";
        }
    }

};

#endif