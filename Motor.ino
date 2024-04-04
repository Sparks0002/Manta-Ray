/****************************************************************************** 

This program is a motor class that will hold port data and control the motor itself.
There are several useful debug and informational member functions as well as utility functions
to both extract useful data and operate any given motor. It requires, at minimum, the ports for the
direction pin, the enable pin, and the step pin.

******************************************************************************/
class Motor {
  private:
    bool killswitch;
  public:
    int MS1;    // Port of MS1
    int MS2;    // Port of MS2
    int dir;    // Port of Dir. "Low" = "Forward" , "High" = "Reverse"
    int EN;     // Port of EN. Pulling low will alllow motor control
    int step;   // Port of Step.
  
  /*
  * Default Constructor that does not set any port.
  */
  Motor::Motor(){
    MS1 = 0;
    MS2 = 0;
    dir = 0;
    EN = 0;
    step = 0;
  }

  /*
  * Constructor that does not set microstep configurations.
  */
  Motor::Motor(int direction, int enable, int stp){
    dir = direction;
    EN = enable;
    step = stp;
    MS1 = 0;    // Disabled by Default
    MS2 = 0;    // Disabled by Default
  }

  /*
  * Constructor that can set all pinouts.
  */
  Motor::Motor(int direction, int enable, int stp, int micro1, int micro2){
    dir = direction;
    EN = enable; 
    step = stp;
    MS1 = micro1;
    MS2 = micro2;
  }

  /*
  * Member Function
  * Set the port of the direction pin.
  */
  void Motor::set_direction(int direction){
      dir = direction;
  }

  /*
  * Member Function
  * Set the port of the step pin.
  */
  void Motor::set_step(int val) {
      step = val;
  }

  /*
  * Member Function
  * Set the port of the Enable Pin
  */
  void Motor::set_enable(int val){
      EN = val;
  }

  /*
  * Member Function
  * Set the port of the Microstep 1 Pin
  */
  void Motor::MicroStep1(int Micro1){
      MS1 = Micro1;
  }

  /*
  * Member Function
  * Set the port of the Microstep 2 Pin
  */
  void Motor::MicroStep2(int Micro2){
      MS2 = Micro2;
  }

  /*
  * Member Function
  * States port of the direction pin
  */
  int Motor::getDir(){
    return dir;
  }

  /*
  * Member Function
  * States the port of the enable pin
  */
  int Motor::getEnable(){
    return EN;
  }

  /*
  * Member Function
  * States the port of the step pin
  */
  int Motor::getStep(){
    return step;
  }

  /*
  * Member Function
  * Set the port of the MS1 Pin
  */
  int Motor::getMS1(){
    return MS1;
  }

  /*
  * Member Function
  * Set the port of the MS2 Pin
  */
  int Motor::getMS2(){
    return MS2;
  }

  /*
  * This function will set the pinout for all the pins to control the motor.
  * Order: Step, Direction, MS1, MS2, Enable
  */
  void Motor::Pin_out(int STP, int DIR, int MS1, int MS2, int EN){
      pinMode(STP, OUTPUT);
      pinMode(DIR, OUTPUT);
      pinMode(MS1, OUTPUT);
      pinMode(MS2, OUTPUT);
      pinMode(EN, OUTPUT);
  }

  /*
  * This function will set the pinout for all the pins to control the motor based on 
  * the preset configurations
  */
  void Motor::Pin_out_internal(){
      pinMode(step, OUTPUT);
      pinMode(dir, OUTPUT);
      pinMode(MS1, OUTPUT);
      pinMode(MS2, OUTPUT);
      pinMode(EN, OUTPUT);
  }

  /*
  * This function will reset the pinouts of all the control signals.
  */
  void Motor::reset_Pins()
  {
    digitalWrite(step, LOW);
    digitalWrite(dir, LOW);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(EN, HIGH);
  }

  /*
  * Debug function that steps the motor forward a specified number of times with a specified delay.
  * This function operates the motor in the "forward" direction.
  */
  void Motor::step_forward(int time_delay, int step_count){
      digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
      for(int x = 0; x < step_count; x++)  //Loop the forward stepping enough times for motion to be visible
      {
        digitalWrite(step,HIGH); //Trigger one step forward
        delay(time_delay);
        digitalWrite(step,LOW); //Pull step pin low so it can be triggered again
        delay(time_delay);
      }
  }

  /*
  * Debug function that steps the motor forward a specified number of times with a specified delay.
  * This function operates the motor in the "reverse" direction.
  */
  void Motor::reverse_step(int time_delay, int step_count){
      digitalWrite(dir, HIGH); //Pull direction pin low to move "reverse"
      for(int x = 0; x<  step_count; x++)  //Loop the forward stepping enough times for motion to be visible
      {
        digitalWrite(step,HIGH); //Trigger one step forward
        delay(time_delay);
        digitalWrite(step,LOW); //Pull step pin low so it can be triggered again
        delay(time_delay);
      }
  }

  /*
  * Debug function that steps the motor forward a specified number of times with a specified delay with 1/8th microstep resolution.
  * This function operates the motor in the "forward" direction.
  */
  void Motor::micro_step(int time_delay, int step_count){
      digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
      digitalWrite(MS1, HIGH); // forcing MS1, and MS2 high to set logic to 1/8th microstep resolution
      digitalWrite(MS2, HIGH);
      for(int x = 0; x < step_count; x++)  //Loop the forward stepping enough times for motion to be visible
      {
        digitalWrite(step,HIGH); //Trigger one step forward
        delay(time_delay);
        digitalWrite(step,LOW); //Pull step pin low so it can be triggered again
        delay(time_delay);
      }
  }
  
};
