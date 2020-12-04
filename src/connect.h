#ifndef _CONNECT_H
#define _CONNECT_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "nvs_flash.h"

#include <vector>
#include <string>

void RegisterEndPoints(void);

class wifi_server {
    public:
    wifi_server();
    void wifiInit();

    static esp_err_t event_handler(void *ctx, system_event_t *event);

    private:
    const int MAX_AP_RECORDS=20;
    static const char* getAuthModeName(const wifi_auth_mode_t auth_mode);
};

#endif 