#ifndef ESP_MASTER_H
#define ESP_MASTER_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1 // Define the channel for ESP-NOW communication

class EspMaster {
    private:
        esp_now_peer_info_t peerInfo; // Structure to hold peer information
        uint8_t dataToSend; // Data to be sent

    public:
        // Constructor
        EspMaster(esp_now_peer_info_t peerInfo, uint8_t dataToSend);

        // Setup function to initialize ESP-NOW
        void setup();

        // Function to send data to the slave
        void sendData(uint8_t data);

        // Callback function for data sent confirmation
        static void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

        void ScanForPeers();
};   

#endif // ESP_MASTER_H