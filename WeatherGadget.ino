#include <Arduino.h>
#include <WiFi.h>

const char *ap_ssid = "ESP32";
const char *ap_pass = "ZB";

void setup()
{
    Serial.begin(115200);

    Serial.println("Iniciando AP");
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(ap_ssid, ap_pass);

    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void loop()
{
    delay(500);
}