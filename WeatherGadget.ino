#include <Arduino.h>
#include "Gadget/App.hpp"
#include "Gadget/Clock.hpp"

typedef unsigned int size_t;

String ssid = "INFINITUM97B6";
String pass = "6plpze1kuK";

String location = "Sabinas,MX";
String apiKey = "4b6e7642b0809e91ae7b7b28ec0632eb";

String zone = "America";
String region = "Monterrey";

Gadget gadget;
Clock gclock;

WiFiServer server(80);

void printWeather(const Weather& weather)
{
    Serial.print("Estado: ");
    Serial.println(weather.state);
    Serial.print("Descripcion: ");
    Serial.println(weather.description);
    Serial.print("Temperartura: ");
    Serial.println(weather.temp);
    Serial.print("Temperartura minima: ");
    Serial.println(weather.tempMin);
    Serial.print("Temperartura maxima: ");
    Serial.println(weather.tempMax);
    Serial.print("Presion: ");
    Serial.println(weather.pressure);
    Serial.print("Humedad: ");
    Serial.println(weather.humidity);
    Serial.print("Velocidad del viento: ");
    Serial.println(weather.windSpeed);
}

void printDateTime(const DateTime& datetime)
{
    Serial.print("Fecha: ");
    Serial.println(datetime.date);
    Serial.print("Hora: ");
    Serial.println(datetime.time);
}

void setup()
{
    Serial.begin(115200);
    initWiFi(ssid, pass);
    gadget.initDisplay();
    //
    gadget.setLocation(location);
    gadget.setApiKey(apiKey);
    gadget.setZone(zone);
    gadget.setRegion(region);
}

void updateGadget() {

    // Actualizar cada 1 minuto
    if(gclock.elapsed() > (1 * MINUTE)) {
        gclock.restart();
        //
        gadget.updateWeather();
        printWeather(gadget.wdata);
        gadget.updateDateTime();
        printDateTime(gadget.ddata);
    }
    // Dibujar OLED
    gadget.drawOLED();

}

void loop()
{
    Serial.print("To test put on web server: http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    WiFiClient client = server.available();
    if(client) {
        String message = "";
        while(client.available()) {
            char c = client.read();
            message += c;
            Serial.print(c);
        }
        Serial.println(c);
    }
    updateGadget();
    delay(100);
}
