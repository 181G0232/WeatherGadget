#ifndef GADGET_APP
#define GADGET_APP

#include <Arduino.h>
#include "Layout.hpp"
#include "LayoutJson.hpp"
#include "Net.hpp"
#include "DrawData.hpp"

class Gadget {

public:
    Adafruit_SSD1306 display;
    WeatherLink wlink;
    Weather wdata;
    DateTimeLink dlink;
    DateTime ddata;

    void setLocation(const String& value) { wlink.location = value; }
    void setApiKey(const String& value) { wlink.apiKey = value; }
    void setZone(const String& value) { dlink.zone = value; }
    void setRegion(const String& value) { dlink.region = value; }

    Gadget() : display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1) {}

    Gadget(const String& location, const String& apiKey, const String& zone, const String& region)
        : display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1), wlink(location, apiKey), dlink(zone, region) 
    {}

    bool initDisplay() {
        Serial.println("Iniciando pantalla OLED");
        // Iniciar pantalla OLED en la dirección 0x3C
        if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
            Serial.println("No se encuentra la pantalla OLED");
            return true;
        }
        return false;
    }

    bool updateWeather() {
        if(WiFi.status() == WL_CONNECTED)
        {
            String jsonText = httpGETRequest(wlink.getUrl());
            //Serial.println(jsonText);
            wdata = Weather(jsonText);
            return true;
        }
        return false;
    }

    bool updateDateTime() {
        if(WiFi.status() == WL_CONNECTED)
        {
            String jsonText = httpGETRequest(dlink.getUrl());
            //Serial.println(jsonText);
            ddata = DateTime(jsonText);
            return true;
        }
        return false;
    }

    void drawOLED() {

        display.clearDisplay();
    
        display.cp437(true);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        
        display.setCursor(0,0);
        
        display.drawRect(0, 0, 128, 64, WHITE);
        
        display.setCursor(4,4);
        
        display.println(ddata.time);

        if (wdata.description == "bloken clouds" || wdata.description == "overcast clouds"){
            display.drawBitmap(92, 28, bloken_clouds_raw, 32, 32, 1);
        }
        else if(wdata.description == "clear sky") 
        {  
            if(ddata.esDia) {
                display.drawBitmap(92, 28, clear_sky_day_raw, 32, 32, 1);
            }
            else {
                display.drawBitmap(92, 28, clear_sky_nigth_raw, 32, 32, 1);
            }
        }
        else if(wdata.description == "few clouds") 
        {  
            if(ddata.esDia) {
                display.drawBitmap(92, 28, few_clouds_day_raw, 32, 32, 1);
            }
            else {
                display.drawBitmap(92, 28, few_clouds_night_raw, 32, 32, 1);
            }
        }
        else if(wdata.description == "mist") 
        {  
            if(ddata.esDia) {
                display.drawBitmap(92, 28, mist_day_raw, 32, 32, 1);
            }
            else {
                display.drawBitmap(92, 28, mist_night_raw, 32, 32, 1);
            }
        }
        else if(wdata.description == "rain" || wdata.description == "light rain")
        {
            display.drawBitmap(92, 28, rain_raw, 32, 32, 1);
        }
        else if(wdata.description == "scattered clouds")
        {
            display.drawBitmap(92, 28, scattered_clouds_raw, 32, 32, 1);
        }
        else if(wdata.description == "shower rain" || wdata.description == "drizzle")
        {
            display.drawBitmap(92, 28, shower_rain_raw, 32, 32, 1);
        }
        else if(wdata.description == "snow")
        {
            display.drawBitmap(92, 28, snow_raw, 32, 32, 1);
        }
        else if(wdata.description == "thunderstorm")
        {
            display.drawBitmap(92, 28, thunderstorm_raw, 32, 32, 1);
        }
        else
        {
            Serial.print("Estado no manejado del clima: ");
            Serial.println(wdata.description);
            return;
        }

        display.setCursor(64,4);
        
        //display.print("Fecha: ");
        display.println(ddata.date);
        //display.print("Hora: ");

        display.setTextSize(2);

        display.setCursor(4,28);

        display.print(wdata.conversionActual);
        
        display.write(248);
        display.println("C");

        display.setTextSize(1);

        display.setCursor(4,44);
        display.println(wdata.state);
        display.setCursor(4,53);
        display.print(wdata.description);

        //display.drawBitmap(96, 32, image_data_Saraarray, 32, 32, 1);

        display.display();

    }

};

#endif