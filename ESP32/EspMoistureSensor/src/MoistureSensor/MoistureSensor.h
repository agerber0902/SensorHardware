#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

#include <Arduino.h>

class MoistureSensor {
private:
    int connectedLedPin; // Pin connected to the LED indicating the sensor is connected
    int alertLedPin; // Pin connected to the LED indicating an alert
    int inputPin; // Pin connected to the moisture sensor input
    
    float sensorVoltage; // Voltage of the sensor input

    float sensorAlertThreshold; // Threshold for alerting the moisture level is low
    float voltageReference; // Reference voltage for the analog input
    float analogResolution; // Resolution of the analog input (default is 4095 for 12-bit ADC)

public:
    // Constructor
    MoistureSensor(int connectedLed, int alertLed, int input, float sensorVoltage, float sensorAlertThreshold,  float vRef = 3.3, float resolution = 4095.0);

    // Setup function to initialize pins
    void setup();

    // Function to read moisture level
    float getMoisture();

    // Light Alert LED
    void setAlertLed();

    // Helper functions
    float readFromAnalog();
    float analogToVoltage(float value);
};

#endif // MOISTURE_SENSOR_H