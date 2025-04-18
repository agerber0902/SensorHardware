#include "EspNow/EspPeer.h"

// Constructor
EspPeer::EspPeer(String ssid, String password, uint8_t &receivedData)
    : SSID(ssid), password(password), receivedData(&receivedData) {}

// Setup function to initialize the peer
void EspPeer::setup()
{
    Serial.begin(921600);
    Serial.println("ESP-NOW Peer Setup..");

    WiFi.mode(WIFI_AP);                   // Set WiFi mode to Access Point
    WiFi.softAP(SSID, password, CHANNEL); // Set up the Access Point with SSID and password

    esp_now_init();                                    // Initialize ESP-NOW
    esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *data, int len) {
        EspPeer::OnDataReceived(mac, data, len, this);
    }); // Register the receive callback function

    Serial.println("ESP-NOW Peer Setup Complete.");
}

void EspPeer::OnDataReceived(const uint8_t *mac, const uint8_t *data, int len, EspPeer *peer)
{
    Serial.printf("Data received from MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("Data length: %d\n", len);
    Serial.printf("Data: ");
    for (int i = 0; i < len; ++i)
    {
        Serial.printf("%02x ", data[i]);
    }
    Serial.println();
    if (len > 0 && peer->receivedData != nullptr)
    {
        *(peer->receivedData) = data[0];
    }
        *receivedData = data[0];
    }
}