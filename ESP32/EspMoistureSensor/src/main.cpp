#include <Arduino.h>
#include "MoistureSensor/MoistureSensor.h"

// Define pins
#define MOISTURE_SENSOR_CONNECTED_LED 2
#define MOISTURE_SENSOR_ALERT_LED 3
#define MOISTURE_SENSOR_INPUT_PIN 34

// Create an instance of MoistureSensor
MoistureSensor moistureSensor(MOISTURE_SENSOR_CONNECTED_LED, MOISTURE_SENSOR_ALERT_LED, MOISTURE_SENSOR_INPUT_PIN, 0, 0.9);

void setup() {
    Serial.begin(921600);
    Serial.println("Beginning Setup...");
    moistureSensor.setup(); // Initialize the sensor
}

void loop() {
    float value = moistureSensor.getMoisture(); // Get the moisture level
    moistureSensor.setAlertLed(); // Set the alert LED based on moisture level
    Serial.println(value); // Print the moisture sensor value to the serial monitor
    delay(1000); // Wait for 1 second before repeating
}