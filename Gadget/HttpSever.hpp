#if !defined(GADGET_SERVER_HPP)
#define GADGET_HTTPSERVER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include "HttpGetRequest.hpp"
#include "HttpGetResponse.hpp"

typedef void(*HttpHandler)(const HttpGetRequest& request, HttpGetResponse& response);

class HttpServer
{

public:
    WiFiServer server;
    unsigned long currentTime;
    unsigned long previousTime;
    unsigned long timeoutTime;

    HttpGetRequest request;
    HttpGetResponse response;
    HttpHandler httphandler;

    HttpServer() : server(80), currentTime(millis()), previousTime(0), timeoutTime(2000)
    {
    }

    void start(HttpHandler httphandler) {
        this->httphandler = httphandler;
        server.begin();
    }

    void stop() {
        server.stop();
    }

    void process()
    {

        WiFiClient client = server.available();
        if (client)
        { 
            Serial.println("Nuevo cliente");
            currentTime = millis();
            previousTime = currentTime;
            String requ;
            requ.reserve(1024);
            while (client.connected() && currentTime - previousTime <= timeoutTime)
            { 
                currentTime = millis();
                if (client.available())
                {                           
                    char c = client.read();
                    Serial.write(c);        
                    requ += c;
                    if (c == '\n')
                    { 
                        requ.trim();
                        request.clear();
                        request.readFrom(requ);
                        //
                        String resp;
                        resp.reserve(1024);
                        response.clear();
                        //
                        httphandler(request, response);
                        response.writeTo(resp);
                        //
                        client.println(resp);
                        break;
                    }
                }
            }
            requ.clear();
            client.stop();
            Serial.println("Cliente desconectado");
        }
    }
};

#endif // GADGET_HTTPSERVER_HPP
