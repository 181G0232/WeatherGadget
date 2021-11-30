#if !defined(GADGET_SERVER_HPP)
#define GADGET_HTTPSERVER_HPP

#include <Arduino.h>
#include <WiFi.h>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

typedef void(*HttpHandler)(const HttpRequest& request, HttpResponse& response);

class HttpServer
{

public:
    WiFiServer server;
    unsigned long currentTime;
    unsigned long previousTime;
    unsigned long timeoutTime;

    HttpRequest* requests;
    size_t requests_num;
    HttpResponse response;
    HttpHandler httphandler;

    HttpServer() : server(80), currentTime(millis()), previousTime(0), timeoutTime(2000)
    {
    }

    void start(HttpHandler httph, HttpRequest* requestsp, size_t requests_n) {
        httphandler = httph;
        requests = requestsp;
        requests_num = requests_n;
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
            String currentLine;
            currentLine.reserve(1024);
            while (client.connected() && currentTime - previousTime <= timeoutTime)
            { 
                currentTime = millis();
                if (client.available())
                {                           
                    char c = client.read();
                    // Serial.write(c);        
                    requ += c;
                    if (c == '\n')
                    { 
                        if (currentLine.length() == 0)
                        {
                            bool matched = false;
                            for(size_t i = 0; i < requests_num; i++) {
                                if(requests[i].match(requ)) {
                                    httphandler(requests[i], response);
                                    //
                                    String resp;
                                    resp.reserve(1024);
                                    response.make(resp);
                                    //
                                    client.println(resp);
                                    matched = true;
                                    break;
                                }
                            }
                            //
                            if(matched) {
                                Serial.println("Se ha procesado el REQUEST. Una respuesta debe haber sido recibida por el cliente");
                            }
                            else {
                                Serial.println("No se ha procesado el REQUEST. Ninguna respuesta fue enviada");
                            }
                            //
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
            requ.clear();
            client.stop();
            Serial.println("Cliente desconectado");
        }
    }
};

#endif // GADGET_HTTPSERVER_HPP
