//Servo library
#include <Servo.h>

//Make servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//Attaching servos to pins. Making variables instead of directly .attach(pin) makes
//it easier to change just one number and makes it easier to understand code
int servo1Pin = 2;
int servo2Pin = 3;
int servo3Pin = 4;
int servo4Pin = 5;

//Potentiometer analog pin assignment. Don't need to have 'A' for 'analog' in front. Just makes for easier identification.
int joystick1XPin = A0;
int joystick1YPin = A1;
int joystick2XPin = A2;
int joystick2YPin = A3;

//Servo's halfway/at rest position
int servo1Position = 90;
int servo2Position = 90;
int servo3Position = 90;
int servo4Position = 90;

//Joystick default speed
int joystick1Acceleration = 0;
int joystick2Acceleration = 0;
int joystick3Acceleration = 0;
int joystick4Acceleration = 0;

void setup()
{
servo1.attach(servo1Pin);
servo2.attach(servo2Pin);
servo3.attach(servo3Pin);
servo4.attach(servo4Pin);
}


void loop()
{
//joystick acceleration breaks joystick's range of motion into 50 equally small parts.
// -512 to provide equal +/- numbers
// +/- 50 to swap directions
// -50. Synchronizes joystick to servos. Rotating joystick clockrise makes servos rotate clockwise
// +50 Reverse joystick and servos controls
// Why -512?
joystick1Acceleration = (analogRead(joystick1XPin) - 512) / -50;
joystick2Acceleration = (analogRead(joystick1YPin) - 512) / -50;
joystick3Acceleration = (analogRead(joystick2XPin) - 512) / -50;
joystick4Acceleration = (analogRead(joystick2YPin) - 512) / -50;

//Mapping position. `constrain` like `map` but limits positioning since not continuous servo
// Updating position like += , -= , /= , *=
servo1Position = constrain((servo1Position + joystick1Acceleration), 1, 180);
servo2Position = constrain((servo2Position + joystick2Acceleration), 1, 180);
servo3Position = constrain((servo3Position + joystick3Acceleration), 1, 180);
servo4Position = constrain((servo4Position + joystick4Acceleration), 1, 180);
//Making servo move to the auto-updating position, servoXPosition
servo1.write(servo1Position);
servo2.write(servo2Position);
servo3.write(servo3Position);
servo4.write(servo4Position);

//controls speed. Found 50 to be sweetspot for speed and smoothness
delay(50);

}
