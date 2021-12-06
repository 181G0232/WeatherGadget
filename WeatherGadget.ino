#include <Arduino.h>
#include "Gadget/Wireless.hpp"
#include "Gadget/HttpSever.hpp"
#include "Gadget/Weather.hpp"
#include "Gadget/DateTime.hpp"

HttpServer server;
Weather weather;
DateTime datetime;

void onHttp(const HttpGetRequest& request, HttpGetResponse& response) {
    /*
        response.status = "200";
        response.contentType = "text/plain";
        response.content = "WORKS:\n";
        response.content += request.method + request.path + request.rawquery;
     */
    //
    Serial.println("Parse QueryString:");
    for(size_t i = 0; i < request.query.count; i++) {
        Serial.print(request.query.kvs[i].key);
        Serial.print(':');
        Serial.println(request.query.kvs[i].value);
    }
    //
    if(request.method == "GET" && request.path == "/get") {
        response.status = "200";
        response.contentType = "application/json";
        response.content += "{\"weather\":{";
            response.content += "\"main\":\"" + weather.main + "\",";
            response.content += "\"description\":\"" + weather.description + "\",";
            response.content += "\"temperature\":" + String(weather.temperature) + "},";
        response.content += "\"datetime\":{";
            response.content += "\"date\":\"" + datetime.date + "\",";
            response.content += "\"time\":\"" + datetime.time + "\",";
            if(datetime.isDay) {
                response.content += "\"isday\":true}}";
            } else {
                response.content += "\"isday\":false}}";
            }
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Inicializando ESP32...");
    initWireless();
    //
    Serial.print("Ingresa en el navegador: ");
    Serial.print(STAIPAddress);
    Serial.println("/get?A=0&B=1");
    //
    weather.updateByApi();
    datetime.updateByApi();
    server.start(onHttp);
}

void loop()
{
    server.process();
    delay(100);
}
