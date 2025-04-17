#include <Arduino.h>

// Define LED pins
#define MOISTURE_SENSOR_CONNECTED_LED 2 // Pin for indicating moisture sensor connection
#define MOISTURE_SENSOR_ALERT_LED 3 // Pin for moisture sensor alert

#define MOISTURE_SENSOR_INPUT_PIN 34 // Pin for moisture sensor input

// End of LED pin definitions

// Define Voltage reference and resolution
#define VOLTAGE_REFERENCE 3.3 // Reference voltage for analog readings
#define ANALOG_RESOLUTION 4095.0 // Resolution for analog readings (12-bit ADC)

// Function declarations
float readFromAnalog(int pin); // Function to read from an analog pin
float analogToVoltage(float value, float referenceVoltage = 3.3, float resolution = 4095.0); // Function to convert analog reading to voltage
float getMoisture(int moisturePin, int index); // Function to get moisture level from a specific pin

void setup() {
  Serial.begin(921600); // Initialize serial communication at 921600 baud rate
  Serial.println("Begining Setup..."); // Print a message to the serial monitor

  // Set pin modes

  // Moisture sensor LED pins
  pinMode(MOISTURE_SENSOR_CONNECTED_LED, OUTPUT);
  pinMode(MOISTURE_SENSOR_ALERT_LED, OUTPUT);

  // Moisturer sensor input pin
  pinMode(MOISTURE_SENSOR_INPUT_PIN, INPUT);

  // End of pin mode setup
}

void loop() {
  Serial.println("Hello, World!"); // Print "Hello, World!" to the serial monitor
  float value = getMoisture(MOISTURE_SENSOR_INPUT_PIN, 0); // Get the moisture level from the sensor
  digitalWrite(MOISTURE_SENSOR_CONNECTED_LED, value > 0); // Turn on the LED
  Serial.println(value); // Print the moisture sensor value to the serial monitor
  delay(1000); // Wait for 1 second before repeating
}


float getMoisture(int moisturePin, int index){
  Serial.print("MOISTURE LEVEL (");
  Serial.print(index);
  Serial.print("): ");
  float value = readFromAnalog(moisturePin);
  Serial.println(value);
  return value;
}

float readFromAnalog(int pin){
  // Dump the first read to negate any noise
  analogRead(pin);
  delay(5);
  return analogToVoltage(analogRead(pin), VOLTAGE_REFERENCE, ANALOG_RESOLUTION);
}

float analogToVoltage(float value, float referenceVoltage, float resolution) {
  // Convert the analog reading to a voltage value
  return (referenceVoltage / resolution) * value;
}