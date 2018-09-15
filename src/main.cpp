//
// Created by Maulik on 9/15/2018.
//

#include <WiFi.h>
#include "time.h"
#include <RemoteDebug.h>

RemoteDebug Debug;

const char* ssid       = "YOUR_SSID";
const char* password   = "YOUR PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800;  // +5.30 Hour
const int   daylightOffset_sec = 0;

void printLocalTime()
{
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        Debug.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    Debug.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
    Serial.begin(115200);

    //connect to WiFi
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());


    //init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();

    //disconnect WiFi as it's no longer needed

    Debug.begin("ESP32");
}

void loop()
{
    delay(1000);
    printLocalTime();
    Debug.handle();
}