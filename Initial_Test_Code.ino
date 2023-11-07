/*
  This program will be used to control a NEMA-17 Stepper Motor through an A4988 Stepper Driver Module.
  The module will be used to significantly reduce the complexity and I/O ports used to control a motor.
  For now, we will denote the turning direction via the built in LED. This will let us assume motion is present even
  without a stepper motor. 

  The actual Manta's motion will be sinusoidal in its wings, however the program itself will not be directy instantiating a waveform
  for it to run with, rather one will be simulated through the Driver Module.
*/

#include <Stepper.h>
#define motorInterfaceType 1; // When using a Driver, interface type must be set to 1 . . . may not be necessary (TBD)
#define SpeedCap 60;

const int stepsPerRevolution = 200; // Will be changed to match our motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Initializing a stepper motor on pins 8-11

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initializing the built-in LED as an output to denote direction turned. This will be disabled in future versions.
  myStepper.setSpeed(SpeedCap); // Units of RPM
  Serial.begin(9600);
}

// The loop function runs over and over again forever
void loop() {

  myStepper.step(stepsPerRevolution);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("clockwise");
  delay(500);                      // wait for half a second

  myStepper.step(stepsPerRevolution);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  Serial.println("counterclockwise");
  delay(500);                      // wait for half a second
}
