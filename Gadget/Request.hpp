#if !defined(GADGET_REQUEST_HPP)
#define GADGET_REQUEST_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

String httpGETRequest(const char* url)
{
    HTTPClient http;

    http.begin(url);

    int httpResponseCode = http.GET();
    String payload;
    payload.reserve(1024);

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP GET exitoso. Codigo: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("HTTP GET fallido. Codigo: ");
        Serial.println(httpResponseCode);
        payload = "{}";
    }

    http.end();

    return payload;
}

#endif // GADGET_REQUEST_HPP
