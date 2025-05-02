#include <IRremote.h>

// Define IR LED pin
const uint8_t sendPin = 3;

// IR parameters
const uint16_t address = 0x5583;
const uint16_t command = 0x6F90;

// Function declarations
void powerOnProjector();
void powerOffProjector();

void setup() {
    Serial.begin(9600); // Initialize hardware serial communication
    IrSender.begin(sendPin); // Initialize IR sender on the specified pin
    Serial.println("Ready to receive serial commands...");
}

void loop() {
    if (Serial.available()) {
        String receivedData = Serial.readStringUntil('\n');
        receivedData.trim();
        Serial.print("Received: ");
        Serial.println(receivedData);

        if (receivedData == "A1") {
            powerOnProjector();
        } else if (receivedData == "A2") {
            powerOffProjector();
        }
    }
}

void powerOnProjector() {
    Serial.println("Sending Power ON command");
    IrSender.sendNEC(address, command, false); // Send NEC command without repeat
}

void powerOffProjector() {
    Serial.println("Sending Power OFF command");
    IrSender.sendNEC(address, command, false); // Send NEC command without repeat
    delay(3000);
    IrSender.sendNEC(address, command, false); // Send NEC command again after delay
}
