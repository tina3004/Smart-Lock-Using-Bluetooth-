#include <BluetoothSerial.h>

// Define the Bluetooth serial object
BluetoothSerial SerialBT;

// Define the relay pin
const int relayPin = 26; 
// Define the password
const char* Master = "1234"; 

void setup() {
  Serial.begin(115200);

  // Initialize Bluetooth serial
  SerialBT.begin("ESP32Bluetooth"); //Bluetooth device name
  Serial.println("Bluetooth Device is Ready to Pair");

  // Set the relay pin as output
  pinMode(relayPin, OUTPUT);
  // Initialize relay to be off
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Check if there's data available to read from Bluetooth
  if (SerialBT.available()) {
    // Read the received data
    String Data = SerialBT.readStringUntil('\n');

    // Trim whitespace from the received data
    Data.trim();

    Serial.println(Data);

    // Check if received data matches the password
    if (Data == Master) {
      // If password is correct, turn on the relay
      digitalWrite(relayPin, HIGH);
      SerialBT.println("Relay activated!");
      delay(5000);
      digitalWrite(relayPin, LOW);

      
    } else {
      // If password is incorrect, do nothing
      SerialBT.println("Incorrect password!");
    }
  }
}