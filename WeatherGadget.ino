#include <Arduino.h>
#include <WiFi.h>

const char *ap_ssid = "ESP32";
const char *ap_pass = "ZB";

void OnWiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_CONNECTED:
        Serial.println("ESP32 connected to WiFi Network");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("ESP32 cisconnected to WiFi Network");
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        Serial.println("Station connected to ESP32 soft AP");
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        Serial.println("Station disconnected from ESP32 soft AP");
        break;
    default:
        break;
    }
}

void setup()
{
    Serial.begin(115200);
    WiFi.onEvent(OnWiFiEvent);

    Serial.println("Iniciando AP");
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(ap_ssid, ap_pass, 13, false, 4);

    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void loop()
{
    delay(500);
}