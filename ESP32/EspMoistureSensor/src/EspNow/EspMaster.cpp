#include "EspNow/EspMaster.h"

// Constructor
EspMaster::EspMaster(esp_now_peer_info_t peerInfo, uint8_t dataToSend)
    : peerInfo(peerInfo), dataToSend(dataToSend) {}

// Setup function to initialize ESP-NOW
void EspMaster::setup()
{
    Serial.begin(921600);

    WiFi.mode(WIFI_STA); // Set WiFi mode to Station

    // Initialize ESP-NOW
    Serial.println("ESP-NOW Master Setup");
    while (esp_now_init() != ESP_OK)
    {
        Serial.println("Initializing ESP-NOW...");
        esp_err_t esp_init = esp_now_init();
        delay(1000);
    }
    Serial.println("ESP-NOW Initialized");

    // Register send callback function
    esp_now_register_send_cb(onDataSent);

    // Scan for peers
    ScanForPeers();

    // Add peers
    esp_now_add_peer(&peerInfo);
}

void EspMaster::ScanForPeers()
{
    int8_t scanResults = WiFi.scanNetworks();

    for (int i = 0; i < scanResults; ++i)
    {
        String SSID = WiFi.SSID(i);
        Serial.printf("Found SSID: %s\n", SSID.c_str());
        String BSSIDstr = WiFi.BSSIDstr(i);
        Serial.printf("BSSID: %s\n", BSSIDstr.c_str());

        // Find peers with SSID starting with "RX"
        if (SSID.indexOf("RX") == 0)
        {

            int mac[6];
            if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]))
            {
                for (int ii = 0; ii < 6; ++ii)
                {
                    peerInfo.peer_addr[ii] = (uint8_t)mac[ii];
                }
            }

            peerInfo.channel = CHANNEL; // pick a channel
            peerInfo.encrypt = 0;       // no encryption
            break;
        }
    }
}

void EspMaster::sendData(uint8_t data)
{
    Serial.println("Sending data to peer...");
    dataToSend = data; // Update the data to send
    Serial.printf("Data to send: %d\n", dataToSend);

    esp_err_t result = esp_now_send(peerInfo.peer_addr, &dataToSend, sizeof(dataToSend));

    if (result == ESP_OK)
    {
        Serial.println("Data sent successfully");
    }
    else
    {
        Serial.printf("Error sending data: %s\n", esp_err_to_name(result));
    }
}

void EspMaster::onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("I sent my data -> ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
}