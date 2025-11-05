#include <Arduino.h>

#define C1 23
#define C2 22
#define M1 18
#define M2 19

volatile long encoderCount = 0;

void setup(){
    Serial.begin(115200);

    pinMode(C1, INPUT_PULLUP);
    pinMode(C2, INPUT_PULLUP);
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);

    // Attach interrupt to channel 1 (C1)
    attachInterrupt(digitalPinToInterrupt(C1), encoderISR, CHANGE);

    // Read initial state
    //lastStateC1 = digitalRead(C1);

    Serial.println("Encoder Interrupt Test Started");
    Serial.println("Rotate the encoder to see counts");
}

void loop(){
    static long lastPrintedCount = 0;

    long currentCount = encoderCount;  // Read volatile variable once
    digitalWrite(M1,LOW);
    anologWrite(M2,80);

    Serial.print("Count: ");
    Serial.print(currentCount);
    Serial.print(" | Change: ");
    Serial.println(currentCount - lastPrintedCount);

    lastPrintedCount = currentCount;

    delay(200);  // Print every 200ms
}

// Interrupt Service Routine (ISR) - Keep it fast!
// Simplified ISR - no need for lastStateC1
void encoderISR() {
    int stateC1 = digitalRead(C1);
    int stateC2 = digitalRead(C2);

    // Since we only trigger on C1 changes, we know it changed
    if (stateC1 == stateC2) {
        encoderCount--;  // Counter-clockwise
    } else {
        encoderCount++;  // Clockwise
    }
}