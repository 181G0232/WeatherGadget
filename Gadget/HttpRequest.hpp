#if !defined(GADGET_HTTPREQUEST_HPP)
#define GADGET_HTTPREQUEST_HPP

#include <Arduino.h>
#include <WiFi.h>

class HttpRequest {

public:

    String method;
    String path;
    String contentType;
    String content;

    HttpRequest() {
        method.reserve(8);
        path.reserve(32);
        contentType.reserve(32);
        content.reserve(1024);
    }

    void clear() {
        method.clear();
        path.clear();
        contentType.clear();
        content.clear();
    }

    void updateByString(const String& httprequest) {
        Serial.println("Request received: ");
        Serial.println(httprequest);
    }

};

#endif // GADGET_HTTPREQUEST_HPP
