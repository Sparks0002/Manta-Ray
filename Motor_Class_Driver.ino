/****************************************************************************** 

This program operates the Motor class by instantiating a motor object with the predefined pinouts.
Three options exist to debug the motor itself. This class will be used to debug 2 motors.

/*************************************************************************
Notes for coding:
Motors are active low to turn them on - we can run a kill switch function to send an active high signal to disable all motors
yellow = en
blue = step
white = dir
Orange = MS1
Green = MS2
Red = Power
Black (Both) = Ground
We want to document the code fully so others could debug this. We want to monitor the number of steps used to complete a rotation
We want to find optimal step sizes for speed and torque
*************************************************************************/
#define stp 2
#define dir 50
#define MS1 4
#define MS2 5
#define EN  6

//Declare variables for functions
char user_input;
int time_delay;
int step_count;

void setup() {
  time_delay = 1; //delay function uses values in milliseconds.
  step_count = 1000;
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. Turn at default microstep mode.");
  Serial.println("2. Reverse direction at default microstep mode.");
  Serial.println("3. Turn at 1/8th microstep mode.");
  Serial.println();
} 

//Main loop
void loop() {
  Motor Motor1 = Motor(dir, EN, stp, MS1, MS2); // Using 5 input constructor to set all pinouts for Motor1
  Motor1.Pin_out_internal();
  while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
      if (user_input =='1')
      {
        Motor1.step_forward(time_delay,step_count);
      }
      else if(user_input =='2')
      {
        Motor1.reverse_step(time_delay,step_count);
      }
      else if(user_input =='3')
      {
        Motor1.micro_step(time_delay,step_count);
      }
      else
      {
        //Serial.println("Invalid option entered.");
      }
      Motor1.reset_Pins();
  }
}
