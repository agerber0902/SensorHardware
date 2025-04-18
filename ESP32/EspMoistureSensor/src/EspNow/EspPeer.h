#ifndef EspPeer_h
#define EspPeer_h

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define CHANNEL 1 // ESP-NOW channel

class EspPeer
{

private:
    String SSID; // Peer SSID
    String password; // Peer password
    uint8_t *receivedData; // Data received from the master

public:
    // Constructor
    EspPeer(String ssid, String password, uint8_t &receivedData);

    // Setup function
    void setup();

    static void OnDataReceived(const uint8_t *mac, const uint8_t *data, int len, EspPeer *peer);

};

#endif