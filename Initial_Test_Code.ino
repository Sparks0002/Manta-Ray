/*
  This program will be used to control a NEMA-17 Stepper Motor through an A4988 Stepper Driver Module.
  The module will be used to significantly reduce the complexity and I/O ports used to control a motor.
  For now, we will denote the turning direction via the built in LED. This will let us assume motion is present even
  without a stepper motor. 

  The actual Manta's motion will be sinusoidal in its wings, however the program itself will not be directy instantiating a waveform
  for it to run with, rather one will be simulated through the Driver Module.
*/

#include <Stepper.h>
#define STEPS 200;
#define motorInterfaceType 1; // When using a Driver, interface type must be set to 1

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initializing the built-in LED as an output to denote direction turned. This will be disabled in future versions.
  int i = 0; // Defining Loop Variable
  stepper.setSpeed(1000); // Setting the maximum speed in steps per second
  bool rise = true; // Boolean control for Oscillation direction
  int SpeedCap = 0;
}

// The loop function runs over and over again forever
void loop() {

  for(i = 10; speedCap < 1000; speedCap+i){
    if(rise){
      stepper.step(i)

    }
  }
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
