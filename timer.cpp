/*
 * This Arduino program demonstrates the use of the TimerOne library to achieve two tasks:
 * 1. Constantly dimming an LED connected to pin 9.
 * 2. Sending a serial message every 100 milliseconds.
 *
 * The LED brightness is controlled using PWM, and the brightness value is adjusted in an interrupt service routine (ISR) 
 * that is called every 30 milliseconds.
 *
 * Another ISR is set to send a serial message every 100 milliseconds.
 *
 * The main loop remains empty as the ISRs handle all necessary operations.
 */

#include <TimerOne.h>

// Pin definitions
const int ledPin = 9;

// Variables for LED dimming
int brightness = 0;
int fadeAmount = 5;

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize Serial for communication
  Serial.begin(9600);

  // Set up Timer1 to call the dimmingLED function every 30 milliseconds
  Timer1.initialize(30000); // 30,000 microseconds = 30 milliseconds
  Timer1.attachInterrupt(dimmingLED);

  // Set up Timer1 to call the sendSerialMessage function every 100 milliseconds
  Timer1.attachInterrupt(sendSerialMessage, 100000); // 100,000 microseconds = 100 milliseconds
}

void loop() {
  // Main loop does nothing, everything is handled by timers
}

// Interrupt service routine for dimming the LED
void dimmingLED() {
  // Dimming the LED
  analogWrite(ledPin, brightness);
  
  // Change the brightness for next time through the loop
  brightness = brightness + fadeAmount;
  
  // Reverse the direction of the fade at the ends of the fade
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
}

// Interrupt service routine for sending a serial message
void sendSerialMessage() {
  Serial.println("Hello, this is a serial message.");
}
