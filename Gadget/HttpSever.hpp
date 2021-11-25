#if !defined(GADGET_SERVER_HPP)
#define GADGET_HTTPSERVER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef void(*HttpHandler)(HttpRequest& request, HttpResponse& response);

class HttpServer
{

public:
    WiFiServer server;
    unsigned long currentTime;
    unsigned long previousTime;
    unsigned long timeoutTime;

    HttpRequest request;
    HttpResponse response;
    HttpHandler httphandler;

    HttpServer() : server(80), currentTime(millis()), previousTime(0), timeoutTime(2000)
    {
    }

    void start(HttpHandler httph) {
        httphandler = httph;
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
            String header;
            header.reserve(1024);
            String currentLine;
            currentLine.reserve(1024);
            while (client.connected() && currentTime - previousTime <= timeoutTime)
            { 
                currentTime = millis();
                if (client.available())
                {                           
                    char c = client.read();
                    Serial.write(c);        
                    header += c;
                    if (c == '\n')
                    { 
                        if (currentLine.length() == 0)
                        {
                            
                            String resp;
                            resp.reserve(1024);
                            request.updateByString(header);
                            response.clear();
                            httphandler(request, response);
                            response.updateToString(resp);
                            client.println(resp);

                            break;
                        }
                        else
                        { 
                            currentLine.clear();
                        }
                    }
                    else if (c != '\r')
                    {                    
                        currentLine += c;
                    }
                }
            }
            header.clear();
            client.stop();
            Serial.println("Cliente desconectado");
        }
    }
};

#endif // GADGET_HTTPSERVER_HPP
