#include <Arduino.h>
#include "Gadget/Wireless.hpp"
#include "Gadget/Weather.hpp"
#include "Gadget/DateTime.hpp"

Weather weather;
DateTime datetime;

void setup() {
    Serial.begin(115200);
    Serial.println("Inicializando ESP32...");
    initNet();
}

void loop() {
    //
    Serial.println("Obteniendo clima desde API...");
    weather.updateByApi();
    Serial.print("Clima: ");
    Serial.println(weather.main);
    Serial.print("Descripcion: ");
    Serial.println(weather.description);
    Serial.print("Temperatura: ");
    Serial.println(weather.temperature);
    //
    Serial.println("Obteniendo fecha y hora desde API...");
    datetime.updateByApi();
    Serial.print("Fecha: ");
    Serial.println(datetime.date);
    Serial.print("Hora: ");
    Serial.println(datetime.time);
    Serial.print("Es de dia: ");
    Serial.println(datetime.isDay);
    //
    delay(1000);
}