#if !defined(GADGET_HTTPRESPONSE_HPP)
#define GADGET_HTTPRESPONSE_HPP

#include <Arduino.h>
#include <WiFi.h>

class HttpResponse {

public:
    String status;
    String contentType;
    String content;

    HttpResponse() {
        status.reserve(32);
        contentType.reserve(32);
        content.reserve(1024);
    }

    void clear() {
        status.clear();
        contentType.clear();
        content.clear();
    }

    void updateToString(String& httpresponse) {
        /*
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:application/json");
        client.println("Connection: close");

        client.println();
        client.println("\"Works\"");
        client.println();
        */
       httpresponse += "HTTP/1.1 " + status + " OK\n";
       httpresponse += "Content-Type: " + contentType + "\n";
       httpresponse += "Connection: close\n";
       httpresponse += "\n" + content + "\n";
       Serial.println("Response to send: ");
       Serial.println(httpresponse);
    }

};

#endif // GADGET_HTTPRESPONSE_HPP
