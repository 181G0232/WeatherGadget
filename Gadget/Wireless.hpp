#if !defined(GADGET_WIRELESS_HPP)
#define GADGET_WIRELESS_HPP

#include <Arduino.h>
#include <WiFi.h>

const char *APSSID = "ESP32_AP";
const char *APPASS = nullptr;
IPAddress APIPAddress;

const char *STASSID = "INFINITUM97B6";
const char *STAPASS = "6plpze1kuK";
IPAddress STAIPAddress;

void initWireless()
{
    Serial.println("Inicializando WiFi...");
    WiFi.mode(WIFI_MODE_STA);
    //
    Serial.println("Inicializando AP...");
    APIPAddress = WiFi.softAP(APSSID, APPASS, 7, false, 1);
    Serial.print("APIP: ");
    Serial.println(APIPAddress);
    //
    Serial.println("Inicializando WiFi...");
    WiFi.begin(STASSID, STAPASS);
    for (auto i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        delay(1000);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Se ha conectado a la red exitosamente");
        STAIPAddress = WiFi.localIP();
        Serial.print("STAIP: ");
        Serial.println(STAIPAddress);
    }
    else
    {
        Serial.println("No se ha podido conectar a la red");
    }
}

#endif // GADGET_WIRELESS_HPP
