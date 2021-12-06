#include <Arduino.h>
#include "Gadget/Wireless.hpp"
#include "Gadget/HttpSever.hpp"
#include "Gadget/Weather.hpp"
#include "Gadget/DateTime.hpp"
#include "Gadget/Oled.hpp"
#include "Gadget/IconSelector.hpp"

HttpServer server;
Weather weather;
DateTime datetime;
Oled oled;

void fillNone() {
    weather.main = "XXXX";
    weather.description = "XXXX";
    weather.temperature = 0;
    datetime.date = "00-00-0000";
    datetime.time = "00:00 XX";
    datetime.isDay = true;
}

void update() {
    weather.updateByApi();
    datetime.updateByApi();
}

void draw() {
    auto icon = selectIcon(weather, datetime);
    //
    oled.clear();
    oled.drawBackground();
    oled.drawTemperature(weather.temperature);
    oled.drawMainWeather(weather.main);
    oled.drawWeatherDescription(weather.description);
    oled.drawDate(datetime.date);
    oled.drawTime(datetime.time);
    //
    if(icon) {
        oled.drawIcon(icon);
    } else {
        Serial.println("No se ha podido determinar el icono");
        Serial.print("Main weather: ");
        Serial.println(weather.main);
        Serial.print("Weather description: ");
        Serial.println(weather.description);
    }
}

void onHttp(const HttpGetRequest& request, HttpGetResponse& response) {
    /*
        response.status = "200";
        response.contentType = "text/plain";
        response.content = "WORKS:\n";
        response.content += request.method + request.path + request.rawquery;
     */
    //
    /*
        Serial.println("Parse QueryString:");
        for(size_t i = 0; i < request.query.count; i++) {
            Serial.print(request.query.kvs[i].key);
            Serial.print(':');
            Serial.println(request.query.kvs[i].value);
        }
     */
    //
    if(request.method == "GET" && request.path == "/info") {
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
    oled.init();
    //
    Serial.print("Ingresa en el navegador: ");
    Serial.print(STAIPAddress);
    Serial.println("/info");
    //
    fillNone();
    update();
    draw();
    server.start(onHttp);
}

unsigned long last = 0;
unsigned long elapsed = 0;

void loop()
{
    elapsed += millis() - last;
    if(elapsed > 60000) {
        last = elapsed;
        elapsed = 0;
        update();
        draw();
    }
    server.process();
    delay(100);
}
