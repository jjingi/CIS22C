#include <Arduino.h>

void touchDetect();

constexpr int LED_PIN = 13;
bool touchTrigger = false; // true when touch detected, false when it is not

void setup() {
  Serial.begin(115200); 
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Touch Sensor Test Started!");
}

void loop() {
    touchDetect();
}

void touchDetect() {
    int capValue = touchRead(5); // Read touch sensor on pin 5

    // if there's touch on pin, print touch detected
    if (capValue > 15000 && !touchTrigger) {
      Serial.println("TOUCH DETECTED!");
      touchTrigger = true;
    }
    else if (capValue < 15000 && touchTrigger) {
      touchTrigger = false; // reset touch trigger when touch is released
    }
    Serial.print("Touch Value: ");
    Serial.println(capValue);
    delay(200);
}

