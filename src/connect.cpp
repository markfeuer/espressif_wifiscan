#include "connect.h"

using namespace std;

#define TAG "SERVER"

/*
class wifi_server {
    public:
    wifi_server();
    void wifiInit();

    static esp_err_t event_handler(void *ctx, system_event_t *event);

    private:
    const int MAX_AP_RECORDS=20;
    static const char* getAuthModeName(const wifi_auth_mode_t auth_mode);
};
*/
const char * wifi_server::getAuthModeName(const wifi_auth_mode_t auth_mode)
{
    vector<string> authName ={"OPEN", "WEP", "WEP PSK", "WEPA2 PSK", "WPA WEPA2 PSK", "MAX"}; 
    return authName[auth_mode].c_str();
};

esp_err_t wifi_server::event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id)
    {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            printf("connecting ....\n ");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            printf("connected ...\n");
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            printf("got ip ...\n");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED :
            printf("disconnected");
            break;
        default:
            printf("Unknown event id %d", event->event_id);
            break; 
    }
    return ESP_OK;
};
    
void wifi_server::wifiInit()
{
    // Expand error checking to handle individual issues
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));    

    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

wifi_server::wifi_server()
{
    wifiInit();
    wifi_scan_config_t scan_config = {
        .ssid=0,                            /**< SSID of AP */
        .bssid=0,                           /**< MAC address of AP */
        .channel=0,                         /**< channel, scan the specific channel */
        .show_hidden=true                 /**< enable to scan AP whose SSID is hidden */
        //.scan_type = WIFI_SCAN_TYPE_ACTIVE, /**< scan type, active or passive */
        //.scan_time =active                  /**< scan time per channel */
    
    };

    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

    wifi_ap_record_t wifi_records[MAX_AP_RECORDS];

    uint16_t maxRecords = MAX_AP_RECORDS;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&maxRecords, wifi_records));

    printf("Found %d access point:\n\n", maxRecords);
    printf("                   SSID       | Channel  | RSSI | Auth Mode \n");
    printf("------------------------------------------------------------\n");
    for(auto &i : wifi_records)
        printf("%32s   | %7d | %4d | %12s |", i.ssid, i.primary, i.rssi, 
        getAuthModeName(i.authmode));
}