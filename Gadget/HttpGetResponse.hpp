#if !defined(GADGET_HTTPGETRESPONSE_HPP)
#define GADGET_HTTPGETRESPONSE_HPP

#include <Arduino.h>

class HttpGetResponse {

public:
    String status;
    String contentType;
    String content;

    HttpGetResponse() {
        status.reserve(8);
        contentType.reserve(32);
        content.reserve(1024);
    }

    void clear() {
        status.clear();
        contentType.clear();
        content.clear();
    }

    void writeTo(String& response) {
        response += "HTTP/1.1 " + status + " OK\n";
        response += "Content-Type: " + contentType + "\n";
        response += "Connection: close\n";
        response += "\n" + content + "\n";
    }

};

#endif // GADGET_HTTPGETRESPONSE_HPP
