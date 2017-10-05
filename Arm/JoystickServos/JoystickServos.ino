// add the servo library
#include <Servo.h>

//define our servos
Servo servol;

//define joystick pins (Analog)
int joyX = 0;
int joyY = 1;
int joyVal;



void setup() {
  // put your setup code here, to run once:
// attached our servos on pins PWM 3-5
servol.attach(3);

}

void loop() {
  // put your main code here, to run repeatedly:
// read the value of joystick (between 0-1023)
joyVal = analogRead(joyX);
joyVal = map (joyVal, 0, 1023, 0, 180); //servo value between 0-180
servol.write(joyVal); //set the servo position according to the joystick value


//joyVal = analogRead(joyY); 
//joyVal = map (joyVal, 0, 1023, 0, 180);
//servol.write(joyVal);
delay(15);
}
