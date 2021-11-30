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
        path.reserve(128);
        contentType.reserve(32);
        content.reserve(1024);
    }

    HttpRequest(const String& method, const String& path, const String& contentType) : HttpRequest() {
        this->method = method;
        this->path = path;
        this->contentType = contentType;
    }

    void clear() {
        method.clear();
        path.clear();
        contentType.clear();
        content.clear();
    }

    bool match(const String& httprequest) {
        auto bk = httprequest.indexOf("\n\n");
        if(bk < 0) bk = httprequest.length();
        //
        Serial.print("Este numero debe ser mas grande que 0: ");
        Serial.println(bk);
        auto ci = 0;
        //
        ci = httprequest.indexOf(method);
        if(ci < 0 || ci > bk) return false;
        Serial.println("Se ha encontrado el method del request 1/3");
        //
        ci = httprequest.indexOf(path);
        if(ci < 0 || ci > bk) return false;
        Serial.println("Se ha encontrado el path del request 2/3");
        //
        ci = httprequest.indexOf(contentType);
        if(ci < 0 || ci > bk) return false;
        Serial.println("Se ha encontrado el content-type del request 3/3");
        //
        content = httprequest.substring(bk);
        content.trim();
        return true;
    }

};

#endif // GADGET_HTTPREQUEST_HPP
