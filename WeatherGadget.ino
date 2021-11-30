#include <Arduino.h>
#include "Gadget/Wireless.hpp"
#include "Gadget/HttpSever.hpp"

HttpServer server;

void onHttp(const HttpGetRequest& request, HttpGetResponse& response) {
    response.status = "200";
    response.contentType = "text/plain";
    response.content = "WORKS:\n";
    response.content += request.method + request.path + request.query;
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
    server.start(onHttp);
}

void loop()
{
    server.process();
    delay(100);
}
