/* WiFi scan Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "connect.h"

#define TAG "DATA"

using namespace std;

xSemaphoreHandle connectionSemaphore;

void setup(){};
void loop(){};

void OnConnected(void *para)
{
    while(true)
    {
        if (xSemaphoreTake(connectionSemaphore, 1000/portTICK_RATE_MS))
        {
            //do somework
            esp_wifi_disconnect();
            xSemaphoreTake(connectionSemaphore, portMAX_DELAY);
        }
        else
        {
            ESP_LOGE(TAG, "Failed to connect. Retry in");
            for(int i =0; i<5; ++i)
            {
                ESP_LOGE(TAG, "..%d", i);
                vTaskDelay(1000/portTICK_RATE_MS);
            }
        }
        
    }
}


void app_main()
{
    wifi_server ws;
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    connectionSemaphore = xSemaphoreCreateBinary();
    ws.wifiInit();
    xTaskCreate(&OnConnected, "handle comms", 1024*5, NULL, 5, NULL);
}

//#include "sdkconfig.h"
//#include <Arduino.h>
//#include <WiFi.h>
   
   /*
void wifiScan() {
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
}

#if !CONFIG_AUTOSTART_ARDUINO
void arduinoTask(void *pvParameter) {
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.begin(115200);
    delay(100);

    while(1) {
        wifiScan();

        // Wait a bit before scanning again
        delay(5000);
    }
}

void app_main()
{
    // initialize arduino library before we start the tasks
    initArduino();

    xTaskCreate(&arduinoTask, "arduino_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
#else
void setup() {
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.begin(115200);
    delay(100);
}

void loop() {
    wifiScan();
    // Wait a bit before scanning again
    delay(5000);
}
#endif 
*/