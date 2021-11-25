#include <Arduino.h>
#include "Gadget/Wireless.hpp"
#include "Gadget/HttpSever.hpp"

HttpServer server;

void onHttpRequest(HttpRequest& request, HttpResponse& response) {
    response.status = "200";
    response.contentType = "application/json";
    response.content = "\"WORKS\"";
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Inicializando ESP32...");
    initWireless();
    //
    Serial.print("Ingresa en el navegador: ");
    Serial.print(STAIPAddress);
    //
    server.start(onHttpRequest);
}

void loop()
{
    server.process();
    delay(100);
}
