#ifndef GADGET_LAYOUT
#define GADGET_LAYOUT

#include <Arduino.h>

/**
 * This class handle the request link to the weather server
 */
class WeatherLink {

public:
    String location;
    String apiKey; 

    String getUrl() const {
        return "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&APPID=" + apiKey;
    }

    WeatherLink() = default;

    WeatherLink(const String& _location, const String& _apiKey)
        : location(_location), apiKey(_apiKey) {}

};

/**
 * This class handle the request link to the datetime server
 */
class DateTimeLink {

public:
    String zone = "America";
    String region = "Monterrey";

    String getUrl() const {
        return "http://worldtimeapi.org/api/timezone/" + zone + "/" + region;
    }

    DateTimeLink() = default;

    DateTimeLink(const String& _zone, const String& _region)
        : zone(_zone), region(_region) {}

};

#endif