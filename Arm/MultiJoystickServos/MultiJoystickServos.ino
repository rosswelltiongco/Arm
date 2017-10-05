#include <Servo.h>

//define our servos. Duplicate to make more servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//define joystick pins (Analog)
int joyStick1X = 0;
int joyStick1Y = 1;
int joyValStick1;

int joyStick2X = 2;
int joyStick2Y = 3;
int joyValStick2;


void setup() {
// attached our servos on pins PWM 3-5
//Duplicate to attach to pins
servo1.attach(3);
servo2.attach(4);
servo3.attach(5);
servo4.attach(6);
  
}

void loop() {
// put your main code here, to run repeatedly:
// read the value of joystick (between 0-1023)
joyValStick1 = analogRead(joyStick1X);
joyValStick1 = map (joyValStick1, 0,1023, 0, 180); //servo value between 0-180
servo1.write(joyValStick1); //set the servo position according to the joystick value

joyValStick1 = analogRead(joyStick1Y);
joyValStick1 = map (joyValStick1, 0,1023, 0, 180); //servo value between 0-180
servo2.write(joyValStick1);//set the servo position according to the joystick value

joyValStick2 = analogRead(joyStick2X); 
joyValStick2 = map (joyValStick2, 0, 1023, 0, 180);
servo3.write(joyValStick2);

joyValStick2 = analogRead(joyStick2Y); 
joyValStick2 = map (joyValStick2, 0, 1023, 0, 180);
servo4.write(joyValStick2);
delay(100); //how responsive program is //wasn't necessary.
}

//Justin's DoubleArmPart (Just having two servos per 1 controller) (2servo x, 1 servo y)
//joyValStick1 = analogRead(joyStick1X);
//joyValStick1 = map (joyValStick1, 0,1023, 0, 180); //servo value between 0-180
//servo1.write(joyValStick1); //set the servo position according to the joystick value

//joyValStick1 = analogRead(joyStick1X);
//joyValStick1 = map (joyValStick1, 0,1023, 0, 180); //servo value between 0-180
//servo2.write(joyValStick1); //set the servo position according to the joystick value
