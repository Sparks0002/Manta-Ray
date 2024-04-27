/****************************************************************************** 

This program operates the Motor class by instantiating a motor object with the predefined pinouts.
Three options exist to debug the motor itself. This class will operate 4 motors simultaneously.

/*************************************************************************
Notes for coding:
Motors are active low to turn them on - we can run a kill switch function to send an active high signal to disable all motors
Motor1
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

// MOTOR 1 (M1)
#define M1_stp 2
#define M1_dir 50
#define M1_MS1 51
#define M1_MS2 50
#define M1_EN  49

// MOTOR 2 (M2)
#define M2_stp 3
#define M2_dir 45
#define M2_MS1 44
#define M2_MS2 43
#define M2_EN 42

//Declare variables for functions
char user_input;
int time_delay; // Lower values inc. Speed, Higher values inc. Torque
int step_count; // Amount of steps for Motor to turn per call. Keep low to simulate simultaneity
int i; // Iteration variable

void setup() {
  time_delay = 1; //delay function uses values in milliseconds.
  step_count = 5; // Keep time delay and step count consisten for all motors.
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
  Motor Motor1 = Motor(M1_dir, M1_EN, M1_stp, M1_MS1, M1_MS2); // Using 5 input constructor to set all pinouts for Motor1
  Motor Motor2 = Motor(M2_dir, M2_EN, M2_stp, M2_MS1, M2_MS2); // Using 5 input constructor to set all pinouts for Motor2
  Motor1.Pin_out_internal();
  Motor2.Pin_out_internal();
  while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(M1_EN, LOW); //Pull enable pin low to allow motor control
      digitalWrite(M2_EN, LOW); 
      if (user_input =='1')
      { 
        for(i = 0; i < 200; i++){
        Motor1.step_forward(time_delay,step_count);
        Motor2.step_forward(time_delay,step_count);
        }
      }
      else if(user_input =='2')
      {
        for(i = 0; i < 200; i++){
        Motor1.reverse_step(time_delay,step_count);
        Motor2.reverse_step(time_delay,step_count);
        }
      }
      else if(user_input =='3')
      {
        for(i = 0; i < 200; i++){
        Motor1.micro_step(time_delay,step_count);
        Motor2.micro_step(time_delay,step_count);
        }
      }
      else
      {
        //Serial.println("Invalid option entered.");
      }
      Motor1.reset_Pins();
      Motor2.reset_Pins();
  }
}
