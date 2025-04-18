#include <Arduino.h>
#include "MoistureSensor/MoistureSensor.h"
#include "EspNow/EspMaster.h"

// Define pins
#define MOISTURE_SENSOR_CONNECTED_LED 2
#define MOISTURE_SENSOR_ALERT_LED 3
#define MOISTURE_SENSOR_INPUT_PIN 34

// Create an instance of MoistureSensor
MoistureSensor moistureSensor(MOISTURE_SENSOR_CONNECTED_LED, MOISTURE_SENSOR_ALERT_LED, MOISTURE_SENSOR_INPUT_PIN, 0, 0.9);

EspMaster espMaster({}, 0); // Create an instance of EspMaster with default parameters

void setup() {
    Serial.begin(921600);
    Serial.println("Beginning Setup...");
    moistureSensor.setup(); // Initialize the sensor
    espMaster.setup(); // Initialize ESP-NOW
    Serial.println("Setup Complete.");
}

void loop() {
    float value = moistureSensor.getMoisture(); // Get the moisture level
    moistureSensor.setAlertLed(); // Set the alert LED based on moisture level
    Serial.println(value); // Print the moisture sensor value to the serial monitor

    // Send the moisture value as data to the slave
    espMaster.sendData((uint8_t)value); 
    delay(10000); // Wait for 1 second before repeating
}