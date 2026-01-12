//Task 1
#include <Arduino.h>

constexpr int LED_PIN = 13;


// 0 --> dot, 1 --> dash
const bool morseJ[4] = {0,1,1,1}; // .---
const bool morseI[2] = {0,0}; // ..
const bool morseN[2] = {1,0}; // -.
const bool morseG[3] = {1,1,0}; // --.

void dot();
void dash();
void printMorse(const bool letter[], int length); 

  
void setup() {
  Serial.begin(115200); 
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  printMorse(morseJ, 4);
  printMorse(morseI, 2);
  printMorse(morseN, 2);
  printMorse(morseG, 3);
  printMorse(morseI, 2);
  delay(2000); // Wait before repeating
}

void dot() {
  digitalWrite(LED_PIN, HIGH); // LED on
  delay(300);               // Dot duration
  digitalWrite(LED_PIN, LOW);  // LED off
  delay(300);  
}

void dash() {
    digitalWrite(LED_PIN, HIGH); // LED on
    delay(900);               // Dash duration
    digitalWrite(LED_PIN, LOW);  // LED off
    delay(300);               // Pause between pulses
}

void printMorse(const bool letter[], int length) {
  for (int i = 0; i < length; i++) {
    // if 0 --> call dot func, if 1 --> dash func
    if (letter[i] == 0) {
      dot();
    } else {
      dash();
    }
  }
  delay(900); // Pause between letters
}

