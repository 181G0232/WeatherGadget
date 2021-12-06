#if !defined(GADGET_ICONSELECTOR_HPP)
#define GADGET_ICONSELECTOR_HPP

#include <Arduino.h>
#include "IconData.hpp"
#include "Weather.hpp"
#include "DateTime.hpp"

const uint8_t*const selectIcon(const Weather& weather, const DateTime& datetime) {
    if (weather.description == "broken clouds" || weather.description == "overcast clouds"){
        return broken_clouds_icon;
    }
    else if(weather.description == "clear sky") 
    {  
        if(datetime.isDay) {
            return clear_sky_day_icon;
        }
        else {
            return clear_sky_nigth_icon;
        }
    }
    else if(weather.description == "few clouds") 
    {  
        if(datetime.isDay) {
            return few_clouds_day_icon;
        }
        else {
            return few_clouds_night_icon;
        }
    }
    else if(weather.description == "mist") 
    {  
        if(datetime.isDay) {
            return mist_day_icon;
        }
        else {
            return mist_night_icon;
        }
    }
    else if(weather.description == "rain" || weather.description == "light rain")
    {
        return rain_icon;
    }
    else if(weather.description == "scattered clouds")
    {
        return scattered_clouds_icon;
    }
    else if(weather.description == "shower rain" || weather.description == "drizzle")
    {
        return shower_rain_icon;
    }
    else if(weather.description == "snow")
    {
        return snow_icon;
    }
    else if(weather.description == "thunderstorm")
    {
        return thunderstorm_icon;
    }
    return nullptr;
}

#endif // GADGET_ICONSELECTOR_HPP
