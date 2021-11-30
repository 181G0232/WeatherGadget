#include <Arduino.h>
#include "Gadget/Wireless.hpp"
#include "Gadget/HttpSever.hpp"

HttpServer server;

HttpRequest requests[] = {
    { "GET", "/SomeAction", " " },
    { "POST", "/SomeAction", "application/json" },
};

void onHttp(const HttpRequest& request, HttpResponse& response) {
    response.status = "200";
    response.contentType = "text/plain";
    response.content = "WORKS:\n";
    response.content += request.method + request.path + request.contentType + request.content;
}

void setup()
{
    Serial.begin(300);
    Serial.println("Inicializando ESP32...");
    initWireless();
    //
    Serial.print("Ingresa en el navegador: ");
    Serial.print(STAIPAddress);
    Serial.println("/SomeAction");
    //
    server.start(onHttp, requests, 2);
}

void loop()
{
    server.process();
    delay(100);
}
