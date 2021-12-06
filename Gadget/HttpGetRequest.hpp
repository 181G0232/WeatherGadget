#if !defined(GADGET_HTTPGETREQUEST_HPP)
#define GADGET_HTTPGETREQUEST_HPP

#include <Arduino.h>
#include "QueryString.hpp"

class HttpGetRequest {

public:
    String method;
    String path;
    String rawquery;
    QueryString query;

    HttpGetRequest() {
        method.reserve(8);
        path.reserve(32);
        rawquery.reserve(64);
    }

    void clear() {
        method.clear();
        path.clear();
        rawquery.clear();
    }

    void readFrom(String& request) {
        request.trim();
        int ei = 0;
        //
        ei = request.indexOf(" ");
        method = request.substring(0, ei);
        method.trim();
        //
        request = request.substring(ei);
        request.trim();
        //
        ei = request.indexOf(" ");
        request = request.substring(0, ei);
        request.trim();
        //
        ei = request.indexOf("?");
        if(ei >= 0) {
            path = request.substring(0, ei);
            rawquery = request.substring(ei);
        } else {
            path = request;
            rawquery.clear();
        }
        //
        Serial.print("Method analizado: ");
        Serial.println(method);
        Serial.print("Path analizado: ");
        Serial.println(path);
        Serial.print("Query analizado: ");
        Serial.println(rawquery);
        //
        query.parse(rawquery);
    }

};

#endif // GADGET_HTTPGETREQUEST_HPP
