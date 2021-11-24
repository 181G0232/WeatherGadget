#ifndef GADGET_NET
#define GADGET_NET

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "LayoutJson.hpp"

/**
 * This function try to get a WiFi connection
 */
void initWiFi(const String& ssid, const String& pass)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());
    Serial.print("Trying to connect to WiFi");
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.print(".");
        delay(1000);
    }
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected");
        Serial.print("Local IP: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("Failed");
    }
}

/**
 * This function do a HTTP reguest to try get data.
 */
String httpGETRequest(const String& url) {
    HTTPClient http;
        
    http.begin(url.c_str());
    
    int httpResponseCode = http.GET();
    String payload = "{}"; 
    
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();

    return payload;
}

/** 
 * Create a Weather data object using a WeatherLink
 */
Weather getWeather(const WeatherLink& link)
{
    if(WiFi.status() == WL_CONNECTED)
    {
        String jsonText = httpGETRequest(link.getUrl());
        //Serial.println(jsonText);
        return Weather(jsonText);
    }
}

/** 
 * Create a DateTime data object using a DateTimeLink
 */
DateTime getDateTime(const DateTimeLink& link)
{
    if(WiFi.status() == WL_CONNECTED)
    {
        String jsonText = httpGETRequest(link.getUrl());
        //Serial.println(jsonText);
        return DateTime(jsonText);
    }
}

#endif