#include <Arduino.h>

// ============================================================
//  PROJECT  : Terminal-Controlled DC Motor via Relay
//  AUTHOR   :Eng. Samer Alaa Abu Zaina
//
//  HARDWARE CONNECTIONS:
//  -----------------------------------------------
//  Arduino Pin 2  ->  1kΩ Resistor  ->  Transistor Base
//  Transistor Emitter               ->  GND
//  Transistor Collector             ->  Relay Coil Pin 1
//  Relay Coil Pin 2                 ->  +5V
//  Relay COM Pin                    ->  +12V Power Source
//  Relay NO Pin                     ->  Motor Positive (+)
//  Motor Negative (-)               ->  GND
//  Virtual Terminal RXD             <-  Arduino Pin 1 (TX0)
//  Virtual Terminal TXD             ->  Arduino Pin 0 (RX0)
//
//  COMMANDS (type in Virtual Terminal):
//    on  -> Motor starts
//    off -> Motor stops
// ============================================================

#define MOTOR_PIN 2

String inputStr = "";
bool motorOn = false;

void setup()
{
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW); // motor OFF at start

  Serial.begin(9600);
  Serial.println("=== Motor Controller ===");
  Serial.println("Type 'on' to start motor");
  Serial.println("Type 'off' to stop motor");
  Serial.println("========================");
}

void loop()
{
  // Read full line from Virtual Terminal
  while (Serial.available())
  {
    char c = Serial.read();

    if (c == '\n' || c == '\r')
    {
      // Process command when Enter is pressed
      inputStr.trim();
      inputStr.toLowerCase();

      if (inputStr == "on")
      {
        digitalWrite(MOTOR_PIN, HIGH);
        motorOn = true;
        Serial.println(">> Motor ON");
      }
      else if (inputStr == "off")
      {
        digitalWrite(MOTOR_PIN, LOW);
        motorOn = false;
        Serial.println(">> Motor OFF");
      }
      else if (inputStr.length() > 0)
      {
        Serial.println(">> Unknown command. Use 'on' or 'off'");
      }

      inputStr = ""; // clear for next command
    }
    else
    {
      inputStr += c; // build the command string
    }
  }
}
