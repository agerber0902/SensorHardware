#include "MoistureSensor.h"

// Constructor
MoistureSensor::MoistureSensor(int connectedLed, int alertLed, int input, float voltage, float threshold, float vRef, float resolution)
    : connectedLedPin(connectedLed), alertLedPin(alertLed), inputPin(input), sensorVoltage(voltage), sensorAlertThreshold(threshold), voltageReference(vRef), analogResolution(resolution) {}

// Setup function to initialize pins
void MoistureSensor::setup() {
    pinMode(connectedLedPin, OUTPUT);
    pinMode(alertLedPin, OUTPUT);
    pinMode(inputPin, INPUT);
}

// Function to read moisture level
float MoistureSensor::getMoisture() {
    float value = readFromAnalog();
    digitalWrite(connectedLedPin, value > 0); // Turn on the LED if value > 0
    return value;
}

// Function to light the alert LED
void MoistureSensor::setAlertLed() {
    digitalWrite(alertLedPin, (sensorVoltage / voltageReference) <= sensorAlertThreshold );
    return;
}

// Helper function to read from analog pin
float MoistureSensor::readFromAnalog() {
    analogRead(inputPin); // Dump the first read to negate noise
    delay(5);
    return analogToVoltage(analogRead(inputPin));
}

// Helper function to convert analog reading to voltage
float MoistureSensor::analogToVoltage(float value) {
    sensorVoltage = (voltageReference / analogResolution) * value;
    return sensorVoltage;
}