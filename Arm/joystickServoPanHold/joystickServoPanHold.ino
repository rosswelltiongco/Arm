//Servo library
#include <Servo.h>

//Make servo objects
Servo servo1;
Servo servo2;      

//Attaching servos to pins. Making variables instead of directly .attach(pin) makes
//it easier to change just one number and makes it easier to understand code
int servo1Pin = 4;
int servo2Pin = 3;

//Potentiometer analog pin assignment. Don't need to have 'A' for 'analog' in front. Just makes for easier identification.
int joystick1XPin = A0;
int joystick1YPin = A1;

//Servo's halfway/at rest position
int servo1Position = 90;
int servo2Position = 90;

//Joystick default speed
int joystick1Acceleration = 0;
int joystick2Acceleration = 0;

void setup()
{
servo1.attach(servo1Pin);
servo2.attach(servo2Pin);
}


void loop()
{
joystick1Acceleration = (analogRead(joystick1XPin) - 512) / 50;
    // -512 to provide equal +/- numbers
joystick2Acceleration = (analogRead(joystick1YPin) - 512) / -50;

//Mapping position. `constrain` like `map` but limits positioning since not continuous servo
servo1Position = constrain((servo1Position + joystick1Acceleration), 1, 180);
servo2Position = constrain((servo2Position + joystick2Acceleration), 1, 180);


servo1.write(servo1Position);
servo2.write(servo2Position);

//controls speed. Found 50 to be sweetspot for speed and smoothness
delay(50);

}
